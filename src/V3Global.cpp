// -*- mode: C++; c-file-style: "cc-mode" -*-
//*************************************************************************
// DESCRIPTION: Verilator: Common implementations
//
// Code available from: https://verilator.org
//
//*************************************************************************
//
// Copyright 2004-2025 by Wilson Snyder. This program is free software; you
// can redistribute it and/or modify it under the terms of either the GNU
// Lesser General Public License Version 3 or the Perl Artistic License
// Version 2.0.
// SPDX-License-Identifier: LGPL-3.0-only OR Artistic-2.0
//
//*************************************************************************

#include "V3PchAstMT.h"

#include "V3Global.h"

#include "V3EmitV.h"
#include "V3Error.h"
#include "V3File.h"
#include "V3HierBlock.h"
#include "V3LinkCells.h"
#include "V3Parse.h"
#include "V3ParseSym.h"
#include "V3Stats.h"
#include "V3ThreadPool.h"

VL_DEFINE_DEBUG_FUNCTIONS;

#define PRINT_FILE_LINE() std::cout << "File: " << __FILE__ << ", Line: " << __LINE__ << std::endl;
#include <fstream>
//######################################################################
// V3Global

void V3Global::boot() {
    UASSERT(!m_rootp, "call once");
    m_rootp = new AstNetlist;
}

void V3Global::shutdown() {
    VL_DO_CLEAR(delete m_hierPlanp, m_hierPlanp = nullptr);  // delete nullptr is safe
    VL_DO_CLEAR(delete m_threadPoolp, m_threadPoolp = nullptr);  // delete nullptr is safe
#ifdef VL_LEAK_CHECKS
    if (m_rootp) VL_DO_CLEAR(m_rootp->deleteTree(), m_rootp = nullptr);
#endif
}

void V3Global::checkTree() const { rootp()->checkTree(); }

void V3Global::readFiles() {
    // NODE STATE
    //   AstNode::user4p()      // VSymEnt*    Package and typedef symbol names
    const VNUser4InUse inuser4;

    VInFilter filter{v3Global.opt.pipeFilter()};
    V3ParseSym parseSyms{v3Global.rootp()};  // Symbol table must be common across all parsing

    V3Parse parser{v3Global.rootp(), &filter, &parseSyms};

    // Parse the std waivers
    if (v3Global.opt.stdWaiver()) {
        parser.parseFile(
            new FileLine{V3Options::getStdWaiverPath()}, V3Options::getStdWaiverPath(), false,
            "Cannot find verilated_std_waiver.vlt containing built-in lint waivers: ");
    }
    // Read .vlt files
    const V3StringSet& vltFiles = v3Global.opt.vltFiles();
    for (const string& filename : vltFiles) {
        parser.parseFile(new FileLine{FileLine::commandLineFilename()}, filename, false,
                         "Cannot find file containing .vlt file: ");
    }

    // Parse the std package
    if (v3Global.opt.stdPackage()) {
        parser.parseFile(new FileLine{V3Options::getStdPackagePath()},
                         V3Options::getStdPackagePath(), false,
                         "Cannot find verilated_std.sv containing built-in std:: definitions: ");
    }

    // Read top module
    //cubbins

///home/cubbins/black-parrot-sim/black-parrot/bp_top/syn/results/verilator/bp_tethered.e_bp_default_cfg.none.sim.bp-tests.hello_world


/* 
unset VERILATOR_ROOT

cd /home/cubbins/black-parrot-sim#
make -B -C black-parrot/bp_top/syn tire_kick

unset VERILATOR_ROOT
cd /home/cubbins/verilator

unset VERILATOR_ROOT
cd /home/cubbins/verilator/src
code . &

unset VERILATOR_ROOT
cd /home/cubbins/black-parrot-sim/black-parrot/bp_top/test/tb/bp_tethered/
code . &

unset VERILATOR_ROOT
cd /home/cubbins/black-parrot-sim/black-parrot
code . &

unset VERILATOR_ROOT
cd /home/cubbins/black-parrot-sim/black-parrot/bp_top/test/
code . &

unset VERILATOR_ROOT
cd /home/cubbins/black-parrot-sim/black-parrot/bp_top/syn/results/verilator/bp_tethered.e_bp_default_cfg.none.sim.bp-tests.hello_world
code . &

====================
//put other software links here

cd /home/cubbins/opam
here is the result but it doesn't complete, but does
create a result in : out.sv
(base) root@AIPC:/home/cubbins/opam# sail -sv small.sail
initialize_registers
  return = () unknown location
  end return unknown location
  return = () unknown location
  end return unknown location
return -> return/1
=====================
(base) root@AIPC:/home/cubbins/mytorchNN# ls
myNN.py  transF.py  try1.py  try2.py  worksTry2.py
(base) root@AIPC:/home/cubbins/mytorchNN# python myNN.py
SimpleCNN(
  (conv1): Conv2d(1, 64, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1))
  (conv2): Conv2d(64, 128, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1))
  (fc1): Linear(in_features=6272, out_features=1024, bias=True)
  (fc2): Linear(in_features=1024, out_features=10, bias=True)
======================
(base) root@AIPC:/home/cubbins/sail-riscv# c_emulator/riscv_rvfi_RV64
======================
(base) root@AIPC:/home/cubbins/rosetta/main# ls -1
CITING_ROSETTA.md
CLA.md
CONTRIBUTING.md
LICENSE.md
PyRosetta.notebooks
README.md
database
demos
documentation
pyrosetta_scripts
rosetta_scripts_scripts
source
tests
tools



=======================


*/
    PRINT_FILE_LINE();
    printf("\nvconst V3StringList& vFiles = v3Global.opt.vFiles();\n");
    printf("\nparser.parseFile\n");
    printf("\nthe file V3Global.cpp, line 89\n");
    printf("\n**************\n");
    std::ofstream outputFile("/home/cubbins/black-parrot-sim/black-parrot/bp_top/test/tb/bp_tethered/Cubbinsfilenames.txt");
    //reset the recording file for decode
    std::ofstream outputFile22("/home/cubbins/black-parrot-sim/black-parrot/bp_top/test/tb/bp_tethered/out_bp_be_instr_decode.txt");
    outputFile22.close();



    printf("cubbins on 1/25/2025\n");

    const V3StringList& vFiles = v3Global.opt.vFiles();
    for (const string& filename : vFiles) {

        //printf("%s\n",filename);



        printf("%s\n", filename.c_str());



        // Save the filename to the file 


        outputFile << filename << std::endl;

        parser.parseFile(new FileLine{FileLine::commandLineFilename()}, filename, false,
                         "Cannot find file containing module: ");
    }

//TomCubbins *****in testbench.v***** within this file
//bp_top/test/tb/bp_tethered/testbench.sv: 
///home/cubbins/black-parrot-sim/black-parrot/bp_top/test/tb/bp_tethered/testbench.sv

    printf("\n**************\n");
    
const string& filename11 ="/home/cubbins/black-parrot-sim/black-parrot/bp_top/test/tb/bp_tethered/testbench.sv";
//const string& filename22 ="/home/cubbins/black-parrot-sim/black-parrot/bp_top/syn/my_wormhole_module.sv";
const string& filename22 ="/home/cubbins/black-parrot-sim/black-parrot/bp_top/test/tb/bp_tethered/my_wormhole_module.sv";

    printf("%s\n", filename11.c_str());
    printf("%s\n", filename22.c_str());

    //this is the point where a new file is added to the list
    //of files that will be parsed and treated, that are not in flist.vcs
    //the standard file list for black-parrot

    parser.parseFile(new FileLine{FileLine::commandLineFilename()}, filename22, false,
                         "Cannot find file containing module: ");
    printf("\n**************\n");


    // Close the file
    outputFile.close();



    // Read libraries
    // To be compatible with other simulators,
    // this needs to be done after the top file is read
    const V3StringSet& libraryFiles = v3Global.opt.libraryFiles();
    for (const string& filename : libraryFiles) {
        parser.parseFile(new FileLine{FileLine::commandLineFilename()}, filename, true,
                         "Cannot find file containing library module: ");
    }

    // Read hierarchical type parameter file
    const string filename = v3Global.opt.hierParamFile();
    if (!filename.empty()) {
        parser.parseFile(new FileLine{FileLine::commandLineFilename()}, filename, false,
                         "Cannot open file containing hierarchical parameter declarations: ");
    }

    // v3Global.rootp()->dumpTreeFile(v3Global.debugFilename("parse.tree"));
    V3Error::abortIfErrors();

    if (!v3Global.opt.preprocOnly()) {
        // Resolve all modules cells refer to
        V3LinkCells::link(v3Global.rootp(), &filter, &parseSyms);
    }

    V3Global::dumpCheckGlobalTree("cells", false, dumpTreeEitherLevel() >= 9);
}

void V3Global::removeStd() {
    // Delete the std package if unused
    if (!usesStdPackage()) {
        if (AstNodeModule* stdp = v3Global.rootp()->stdPackagep()) {
            v3Global.rootp()->stdPackagep(nullptr);
            VL_DO_DANGLING(stdp->unlinkFrBack()->deleteTree(), stdp);
        }
    }
}

string V3Global::debugFilename(const string& nameComment, int newNumber) {
    ++m_debugFileNumber;
    if (newNumber) m_debugFileNumber = newNumber;
    return opt.hierTopDataDir() + "/" + opt.prefix() + "_" + digitsFilename(m_debugFileNumber)
           + "_" + nameComment;
}
string V3Global::digitsFilename(int number) {
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(3) << number;
    return ss.str();
}

void V3Global::dumpCheckGlobalTree(const string& stagename, int newNumber, bool doDump) {
    const string treeFilename = v3Global.debugFilename(stagename + ".tree", newNumber);
    if (dumpTreeLevel()) v3Global.rootp()->dumpTreeFile(treeFilename, doDump);
    if (dumpTreeJsonLevel()) {
        v3Global.rootp()->dumpTreeJsonFile(treeFilename + ".json", doDump);
    }
    if (v3Global.opt.dumpTreeDot()) {
        v3Global.rootp()->dumpTreeDotFile(treeFilename + ".dot", doDump);
    }
    if (v3Global.opt.stats()) V3Stats::statsStage(stagename);

    if (doDump && v3Global.opt.debugEmitV()) V3EmitV::debugEmitV(treeFilename + ".v");
    if (v3Global.opt.debugCheck() || dumpTreeEitherLevel()) {
        // Error check
        v3Global.rootp()->checkTree();
        // Broken isn't part of check tree because it can munge iterp's
        // set by other steps if it is called in the middle of other operations
        V3Broken::brokenAll(v3Global.rootp());
    }
}

void V3Global::idPtrMapDumpJson(std::ostream& os) {
    std::string sep = "\n  ";
    os << "\"pointers\": {";
    for (const auto& itr : m_ptrToId) {
        os << sep << '"' << itr.second << "\": \"" << cvtToHex(itr.first) << '"';
        sep = ",\n  ";
    }
    os << "\n }";
}

void V3Global::saveJsonPtrFieldName(const std::string& fieldName) {
    m_jsonPtrNames.insert(fieldName);
}

void V3Global::ptrNamesDumpJson(std::ostream& os) {
    std::string sep = "\n  ";
    os << "\"ptrFieldNames\": [";
    for (const auto& itr : m_jsonPtrNames) {
        os << sep << '"' << itr << '"';
        sep = ",\n  ";
    }
    os << "\n ]";
}

const std::string& V3Global::ptrToId(const void* p) {
    const auto pair = m_ptrToId.emplace(p, "");
    if (pair.second) {
        std::ostringstream os;
        if (p) {
            os << "(";
            unsigned id = m_ptrToId.size();
            do { os << static_cast<char>('A' + id % 26); } while (id /= 26);
            os << ")";
        } else {
            os << "0";
        }
        pair.first->second = os.str();
    }
    return pair.first->second;
}
