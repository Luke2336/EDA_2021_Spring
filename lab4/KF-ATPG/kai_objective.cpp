
/* =========FOR INTERNAL USE ONLY. NO DISTRIBUTION PLEASE ========== */

/*********************************************************************
 Copyright 2002-2006, University of California at Santa Barbara (UCSB).
 All rights reserved.

 --- This software and any associated documentation is provided "as is"

 UCSB and the authors MAKES NO REPRESENTATIONS OR WARRANTIES, EXPRESS
 OR IMPLIED, INCLUDING THOSE OF MERCHANTABILITY OR FITNESS FOR A
 PARTICULAR PURPOSE, OR THAT  USE OF THE SOFTWARE, MODIFICATIONS, OR
 ASSOCIATED DOCUMENTATION WILL NOT INFRINGE ANY PATENTS, COPYRIGHTS,
 TRADEMARKS OR OTHER INTELLECTUAL PROPERTY RIGHTS OF A THIRD PARTY.

 UCSB and the authors shall not be liable under any circumstances for
 any direct, indirect, special, incidental, or consequential damages
 with respect to any claim by USER or any third party on account of
 or arising from the use, or inability to use, this software or its
 associated documentation, even if UCSB and/or the authors has been advised
 of the possibility of those damages.
*********************************************************************/
// Author: Kai Yang (kyang@ece.ucsb.edu)

using namespace std;

#include "kai_objective.h"
#include "GetLongOpt.h"
#include "kai_gate.h"
#include "kai_path.h"
#include "kai_typeemu.h"
#include <assert.h>
#include <cstdlib>
#include <iostream>
#include <map>
#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>

extern GetLongOpt option;
extern map<string, KaiGATE *> CUTNameTable;

string ToCUTName(KaiGATE *gptr, int TF) {
  char tmp[100];
  sprintf(tmp, "%d", TF);
  string dupname;
  if (gptr->GetFunction() != G_DFF)
    dupname = gptr->GetName() + "_dup_t" + tmp;
  else
    dupname = gptr->GetName() + "_ppi_t" + tmp;
  KaiGATE *tg = CUTNameTable[dupname];
  if (!tg) {
    cerr << "Miss ToCUTName()" << endl;
    exit(-1);
  }
  // cout << dupname << endl;
  return dupname;
}

void AtpgObj::BuildFromPath_NR(PATH *pptr) {
  cleanup();
  KaiGATE *CurG, *PreG;
  TRANSITION CurT, PreT;
  assert(pptr->NoGate() == pptr->NoTrans());

  PreG = pptr->GetGate(0);
  PreT = pptr->GetTrans(0);
  if (PreT == R)
    AddObj(ToCUTName(PreG, 0), 0);
  else if (PreT == F)
    AddObj(ToCUTName(PreG, 0), 1);
  else {
    cerr << "R/F Error !" << endl;
    exit(-1);
  }
  // Fault Activation at 2nd TimeFrame
  if (PreT == R)
    AddObj(ToCUTName(PreG, 1), 1);
  else if (PreT == F)
    AddObj(ToCUTName(PreG, 1), 0);
  else {
    cerr << "R/F Error !" << endl;
    exit(-1);
  }
  for (int i = 1; i < pptr->NoGate(); i++) {
    CurG = pptr->GetGate(i);
    CurT = pptr->GetTrans(i);
    if (CurG->GetFunction() == G_PI) {
      if (CurT == R)
        AddObj(ToCUTName(CurG, 0), 0);
      else if (CurT == F)
        AddObj(ToCUTName(CurG, 0), 1);
      else {
        cerr << "R/F Error !" << endl;
        exit(-1);
      }
      // Fault Activation at 2nd TimeFrame
      if (CurT == R)
        AddObj(ToCUTName(CurG, 1), 1);
      else if (CurT == F)
        AddObj(ToCUTName(CurG, 1), 0);
      else {
        cerr << "R/F Error !" << endl;
        exit(-1);
      }
    } else if (CurG->GetFunction() == G_AND) {
      // cv=0, ncv=1
      if (PreT == R) {
        // x->ncv
        // x->1
        for (int j = 0; j < CurG->NoFanin(); j++) {
          if (PreG != CurG->Fanin(j)) {
            AddObj(ToCUTName(CurG->Fanin(j), 1), 1);
          }
        }
      } else if (PreT == F) {
        // x->ncv
        // x->1
        for (int j = 0; j < CurG->NoFanin(); j++) {
          if (PreG != CurG->Fanin(j)) {
            AddObj(ToCUTName(CurG->Fanin(j), 1), 1);
          }
        }
      } else {
        cerr << "R/F Error !" << endl;
        exit(-1);
      }
    } else if (CurG->GetFunction() == G_NAND) {
      // cv=0, ncv=1
      if (PreT == R) {
        // x->ncv
        // x->1
        for (int j = 0; j < CurG->NoFanin(); j++) {
          if (PreG != CurG->Fanin(j)) {
            AddObj(ToCUTName(CurG->Fanin(j), 1), 1);
          }
        }
      } else if (PreT == F) {
        // x->ncv
        // x->1
        for (int j = 0; j < CurG->NoFanin(); j++) {
          if (PreG != CurG->Fanin(j)) {
            AddObj(ToCUTName(CurG->Fanin(j), 1), 1);
          }
        }
      } else {
        cerr << "R/F Error !" << endl;
        exit(-1);
      }
    } else if (CurG->GetFunction() == G_OR) {
      // cv:1 cnv: 0
      if (PreT == R) {
        // x->ncv
        // x->0
        for (int j = 0; j < CurG->NoFanin(); j++) {
          if (PreG != CurG->Fanin(j)) {
            AddObj(ToCUTName(CurG->Fanin(j), 1), 0);
          }
        }
      } else if (PreT == F) {
        // x->ncv
        // x->0
        for (int j = 0; j < CurG->NoFanin(); j++) {
          if (PreG != CurG->Fanin(j)) {
            AddObj(ToCUTName(CurG->Fanin(j), 1), 0);
          }
        }
      } else {
        cerr << "R/F Error !" << endl;
        exit(-1);
      }
    } else if (CurG->GetFunction() == G_NOR) {
      // cv:1 cnv: 0
      if (PreT == R) {
        // x->ncv
        // x->0
        for (int j = 0; j < CurG->NoFanin(); j++) {
          if (PreG != CurG->Fanin(j)) {
            AddObj(ToCUTName(CurG->Fanin(j), 1), 0);
          }
        }
      } else if (PreT == F) {
        // x->ncv
        // x->0
        for (int j = 0; j < CurG->NoFanin(); j++) {
          if (PreG != CurG->Fanin(j)) {
            AddObj(ToCUTName(CurG->Fanin(j), 1), 0);
          }
        }
      } else {
        cerr << "R/F Error !" << endl;
        exit(-1);
      }
    }
    PreG = CurG;
    PreT = CurT;
  }
}

void AtpgObj::BuildFromPath_R(PATH *pptr) {
  cleanup();
  KaiGATE *CurG, *PreG;
  TRANSITION CurT, PreT;
  assert(pptr->NoGate() == pptr->NoTrans());

  /*Do Fault Activation & Fault Propagation under Robust test setting*/
  PreG = pptr->GetGate(0);
  PreT = pptr->GetTrans(0);
  if (PreT == R)
    AddObj(ToCUTName(PreG, 0), 0);
  else if (PreT == F)
    AddObj(ToCUTName(PreG, 0), 1);
  else {
    cerr << "R/F Error !" << endl;
    exit(-1);
  }

  // Fault Activation at 2nd TimeFrame
  if (PreT == R)
    AddObj(ToCUTName(PreG, 1), 1);
  else if (PreT == F)
    AddObj(ToCUTName(PreG, 1), 0);
  else {
    cerr << "R/F Error !" << endl;
    exit(-1);
  }

  for (int i = 1; i < pptr->NoGate(); i++) {
    CurG = pptr->GetGate(i);
    CurT = pptr->GetTrans(i);
    if (CurG->GetFunction() == G_PI) {
      if (CurT == R)
        AddObj(ToCUTName(CurG, 0), 0);
      else if (CurT == F)
        AddObj(ToCUTName(CurG, 0), 1);
      else {
        cerr << "R/F Error !" << endl;
        exit(-1);
      }

      // Fault Activation at 2nd TimeFrame
      if (CurT == R)
        AddObj(ToCUTName(CurG, 1), 1);
      else if (CurT == F)
        AddObj(ToCUTName(CurG, 1), 0);
      else {
        cerr << "R/F Error !" << endl;
        exit(-1);
      }
    } else if (CurG->GetFunction() == G_AND) {
      // cv=0, ncv=1
      if (PreT == R) {
        // x->ncv
        // x->1
        for (int j = 0; j < CurG->NoFanin(); j++) {
          if (PreG != CurG->Fanin(j)) {
            AddObj(ToCUTName(CurG->Fanin(j), 1), 1);
          }
        }
      } else if (PreT == F) {
        // ncv->ncv
        // 1->1
        for (int j = 0; j < CurG->NoFanin(); j++) {
          if (PreG != CurG->Fanin(j)) {
            AddObj(ToCUTName(CurG->Fanin(j), 0), 1);
            AddObj(ToCUTName(CurG->Fanin(j), 1), 1);
          }
        }
      }
    } else if (CurG->GetFunction() == G_NAND) {
      // cv=0, ncv=1
      if (PreT == R) {
        // x->ncv
        // x->1
        for (int j = 0; j < CurG->NoFanin(); j++) {
          if (PreG != CurG->Fanin(j)) {
            AddObj(ToCUTName(CurG->Fanin(j), 1), 1);
          }
        }
      } else if (PreT == F) {
        // ncv->ncv
        // 1->1
        for (int j = 0; j < CurG->NoFanin(); j++) {
          if (PreG != CurG->Fanin(j)) {
            AddObj(ToCUTName(CurG->Fanin(j), 0), 1);
            AddObj(ToCUTName(CurG->Fanin(j), 1), 1);
          }
        }
      }
    } else if (CurG->GetFunction() == G_OR) {
      // cv:1 cnv: 0
      if (PreT == R) {
        // ncv->ncv
        // 0->0
        for (int j = 0; j < CurG->NoFanin(); j++) {
          if (PreG != CurG->Fanin(j)) {
            AddObj(ToCUTName(CurG->Fanin(j), 1), 0);
            AddObj(ToCUTName(CurG->Fanin(j), 0), 0);
          }
        }
      } else if (PreT == F) {
        // x->ncv
        // x->0
        for (int j = 0; j < CurG->NoFanin(); j++) {
          if (PreG != CurG->Fanin(j)) {
            AddObj(ToCUTName(CurG->Fanin(j), 1), 0);
          }
        }
      }
    } else if (CurG->GetFunction() == G_NOR) {
      // cv:1 cnv: 0
      if (PreT == R) {
        // ncv->ncv
        // 0->0
        for (int j = 0; j < CurG->NoFanin(); j++) {
          if (PreG != CurG->Fanin(j)) {
            AddObj(ToCUTName(CurG->Fanin(j), 1), 0);
            AddObj(ToCUTName(CurG->Fanin(j), 0), 0);
          }
        }
      } else if (PreT == F) {
        // x->ncv
        // x->0
        for (int j = 0; j < CurG->NoFanin(); j++) {
          if (PreG != CurG->Fanin(j)) {
            AddObj(ToCUTName(CurG->Fanin(j), 1), 0);
          }
        }
      }
    }

    PreG = CurG;
    PreT = CurT;
  }
}

void AtpgObj::Dump() {
  assert(_name.size() == _value.size());
  for (unsigned int i = 0; i < _name.size(); ++i) {
    cout << _name[i] << "(" << _value[i] << ") ";
  }
  cout << endl;
}
