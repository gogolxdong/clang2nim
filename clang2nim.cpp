#include <sstream>
#include <string>

#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/ASTConsumers.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "llvm/Support/raw_ostream.h"

using namespace clang;
using namespace clang::driver;
using namespace clang::tooling;

static llvm::cl::OptionCategory ToolingSampleCategory("Tooling Sample");

static std::map<std::string, std::string> TypeTable = {
          {"unsigned int","uint"},
          {"unsigned long","uint64"},
          {"long","int64"},
          {"s64","int64"},
          {"__s32","int32"},
          {"s32","int32"},
          {"__u8","uint8"},
          {"__u16","uint16"},
          {"__u32","uint32"},
          {"__u64","uint64"},
          {"u8","uint8"},
          {"u16","uint16"},
          {"u32","uint32"},
          {"u64","uint64"},
          {"size_t","uint"},
          {"__kernel_size_t","uint"},
          {"__be32","uint32"},
          };

class MyASTVisitor : public RecursiveASTVisitor<MyASTVisitor> {
public:
  MyASTVisitor(Rewriter &R) : TheRewriter(R) {}

  bool VisitStmt(Stmt *s) {
    SourceManager &sm = TheRewriter.getSourceMgr();
    StringRef FileName = "test.nim";
    std::error_code EC;
    auto FileStream = std::make_shared<llvm::raw_fd_ostream>(FileName, EC, llvm::sys::fs::F_Append);
    if (EC) {
      llvm::errs() << "Could not open " << FileName << " for writing\n";
      return true;
    }
    auto langOptions = LangOptions();
    std::string stmtStr; 
    if (isa<IfStmt>(s)) {
      std::string ifStatementStr;
      IfStmt *IfStatement = cast<IfStmt>(s);
      Expr *cond = IfStatement->getCond();
      if (cond) {
        bool invalid;
        SourceManager &sm = TheRewriter.getSourceMgr();
        CharSourceRange conditionRange = CharSourceRange::getTokenRange(cond->getBeginLoc(), cond->getEndLoc());
        StringRef str = Lexer::getSourceText(conditionRange, sm, langOptions , &invalid);
        stmtStr += "if " + str.str() + ":\n";
      }
      Stmt *Else = IfStatement->getElse();
      if (Else) {
        CharSourceRange elseRange = CharSourceRange::getTokenRange(Else->getBeginLoc(), Else->getEndLoc());
        bool invalid;
        StringRef str = Lexer::getSourceText(elseRange, sm, langOptions, &invalid);
        stmtStr += "else: " + str.str() + "\n";
      }
    }else if (isa<BreakStmt>(s)) {
      bool invalid;
      BreakStmt *statement = cast<BreakStmt>(s);
      CharSourceRange range = CharSourceRange::getTokenRange(statement->getBeginLoc(), statement->getEndLoc());
      StringRef str = Lexer::getSourceText(range, sm, langOptions, &invalid);
      stmtStr += str.str() + "\n";
    }else if (isa<ReturnStmt>(s)) {
      bool invalid;
      ReturnStmt *statement = cast<ReturnStmt>(s);
      auto *value = statement->getRetValue();

      CharSourceRange range = CharSourceRange::getTokenRange(statement->getBeginLoc(), statement->getEndLoc());
      StringRef str = Lexer::getSourceText(range, sm, langOptions, &invalid);
      stmtStr += str.str() + "\n";

    }else if (isa<AsmStmt>(s)) {
      bool invalid;
      AsmStmt *statement = cast<AsmStmt>(s);
      CharSourceRange range = CharSourceRange::getTokenRange(statement->getAsmLoc());
      StringRef str = Lexer::getSourceText(range, sm, langOptions, &invalid);
      stmtStr += str.str();
    } else if (isa<DeclStmt>(s)) {
      bool invalid;
      DeclStmt *statement = cast<DeclStmt>(s);
      CharSourceRange range = CharSourceRange::getTokenRange(statement->getBeginLoc(), statement->getEndLoc());
      StringRef str = Lexer::getSourceText(range, sm, langOptions, &invalid);
      stmtStr += str.str() + "\n";
    } else if (isa<ForStmt>(s)) {
      bool invalid;
      ForStmt *statement = cast<ForStmt>(s);
      CharSourceRange range = CharSourceRange::getTokenRange(statement->getBeginLoc(), statement->getEndLoc());
      StringRef str = Lexer::getSourceText(range, sm, langOptions, &invalid);
      stmtStr += str.str();
      } else if (isa<GotoStmt>(s)) {
      bool invalid;
      GotoStmt *statement = cast<GotoStmt>(s);
      CharSourceRange range = CharSourceRange::getTokenRange(statement->getBeginLoc(), statement->getEndLoc());
      StringRef str = Lexer::getSourceText(range, sm, langOptions, &invalid);
      stmtStr += str.str();
      }else if (isa<ContinueStmt>(s)) {
      bool invalid;
      ContinueStmt *statement = cast<ContinueStmt>(s);
      CharSourceRange range = CharSourceRange::getTokenRange(statement->getBeginLoc(), statement->getEndLoc());
      StringRef str = Lexer::getSourceText(range, sm, langOptions, &invalid);
      stmtStr += str.str();
    } else if (isa<WhileStmt>(s)) {
      bool invalid;
      WhileStmt *statement = cast<WhileStmt>(s);
      CharSourceRange range = CharSourceRange::getTokenRange(statement->getBeginLoc(), statement->getEndLoc());
      StringRef str = Lexer::getSourceText(range, sm, langOptions, &invalid);
      stmtStr += str.str();
    } else if (isa<DoStmt>(s)) {
      bool invalid;
      DoStmt *statement = cast<DoStmt>(s);
      CharSourceRange range = CharSourceRange::getTokenRange(statement->getBeginLoc(), statement->getEndLoc());
      StringRef str = Lexer::getSourceText(range, sm, langOptions, &invalid);
      stmtStr += str.str();
    }
    // } else if (isa<AttributedStmt>(s)) {
    //   bool invalid;
    //   AttributedStmt *statement = cast<AttributedStmt>(s);
    //   CharSourceRange range = CharSourceRange::getTokenRange(statement->getBeginLoc());
    //   StringRef str = Lexer::getSourceText(range, sm, langOptions, &invalid);
      // stmtStr += str.str() + "\n";
    // } else if (isa<LabelStmt>(s)) {
    //   bool invalid;
    //   LabelStmt *statement = cast<LabelStmt>(s);
    //   CharSourceRange range = CharSourceRange::getTokenRange(statement->getBeginLoc());
    //   StringRef str = Lexer::getSourceText(range, sm, langOptions, &invalid);
      // stmtStr += str.str() + "\n";
    // } else if (isa<ValueStmt>(s)) {
    //   bool invalid;
    //   ValueStmt *statement = cast<ValueStmt>(s);
    //   CharSourceRange range = CharSourceRange::getTokenRange(statement->getBeginLoc(), statement->getEndLoc());
    //   StringRef str = Lexer::getSourceText(range, sm, langOptions, &invalid);
      // stmtStr += "ValueStmt:" + str.str();
    // } else if (isa<DefaultStmt>(s)) {
    //   bool invalid;
    //   DefaultStmt *statement = cast<DefaultStmt>(s);
    //   CharSourceRange range = CharSourceRange::getTokenRange(statement->getDefaultLoc());
    //   StringRef str = Lexer::getSourceText(range, sm, langOptions, &invalid);
    //   stmtStr += str.str() + "\n";
    // } else if (isa<CaseStmt>(s)) {
    //   bool invalid;
    //   CaseStmt *statement = cast<CaseStmt>(s);
    //   CharSourceRange range = CharSourceRange::getTokenRange(statement->getBeginLoc(), statement->getEndLoc());
    //   StringRef str = Lexer::getSourceText(range, sm, langOptions, &invalid);
    //   stmtStr += "CaseStmt:" + str.str() + "\n";
    // } else if (isa<SwitchCase>(s)) {
    //   bool invalid;
    //   SwitchCase *statement = cast<SwitchCase>(s);
    //   CharSourceRange range = CharSourceRange::getTokenRange(statement->getBeginLoc(), statement->getEndLoc());
    //   StringRef str = Lexer::getSourceText(range, sm, langOptions, &invalid);
    //   // *FileStream << str.str() + "\n" ;
    //   stmtStr += "SwitchCase:" + str.str() + "\n";

    // } else if (isa<CompoundStmt>(s)) {
      
      // bool invalid;
      // CompoundStmt *statement = cast<CompoundStmt>(s);
      // CharSourceRange range = CharSourceRange::getTokenRange(statement->getBeginLoc(), statement->getEndLoc());
      // StringRef str = Lexer::getSourceText(range, sm, langOptions, &invalid);

      // VisitStmt(s);
    // } else if (isa<NullStmt>(s)) {
    //   bool invalid;
    //   NullStmt *statement = cast<NullStmt>(s);
    //   CharSourceRange range = CharSourceRange::getTokenRange(statement->getBeginLoc(), statement->getEndLoc());
    //   StringRef str = Lexer::getSourceText(range, sm, langOptions, &invalid);
      // stmtStr += "NullStmt:" + str.str() + "\n";

    // } else if (isa<SwitchStmt>(s)) {
    //   bool invalid;
    //   SwitchStmt *statement = cast<SwitchStmt>(s);
    //   CharSourceRange range = CharSourceRange::getTokenRange(statement->getBeginLoc(), statement->getEndLoc());
    //   StringRef str = Lexer::getSourceText(range, sm, langOptions, &invalid);
    //   // *FileStream << str +"\n" ;
    //   stmtStr += "SwitchStmt:" + str.str();
   
    
    
    // }else if (isa<IndirectGotoStmt>(s)) {
    //   bool invalid;
    //   IndirectGotoStmt *statement = cast<IndirectGotoStmt>(s);
    //   CharSourceRange range = CharSourceRange::getTokenRange(statement->getBeginLoc(), statement->getEndLoc());
    //   StringRef str = Lexer::getSourceText(range, sm, langOptions, &invalid);
    //   stmtStr += "IndirectGotoStmt:" + str.str();
    
   
    // }else if (isa<GCCAsmStmt>(s)) {
    //   bool invalid;
    //   GCCAsmStmt *statement = cast<GCCAsmStmt>(s);
    //   CharSourceRange range = CharSourceRange::getTokenRange(statement->getBeginLoc(), statement->getEndLoc());
    //   StringRef str = Lexer::getSourceText(range, sm, langOptions, &invalid);
    // }else if (isa<MSAsmStmt>(s)) {
    //   bool invalid;
    //   MSAsmStmt *statement = cast<MSAsmStmt>(s);
    //   CharSourceRange range = CharSourceRange::getTokenRange(statement->getBeginLoc(), statement->getEndLoc());
    //   StringRef str = Lexer::getSourceText(range, sm, langOptions, &invalid);
    //   stmtStr += "MSAsmStmt:" + str.str();
    // }else if (isa<SEHExceptStmt>(s)) {
    //   bool invalid;
    //   SEHExceptStmt *statement = cast<SEHExceptStmt>(s);
    //   CharSourceRange range = CharSourceRange::getTokenRange(statement->getBeginLoc(), statement->getEndLoc());
    //   StringRef str = Lexer::getSourceText(range, sm, langOptions, &invalid);
    //   stmtStr += "SEHExceptStmt:" + str.str();
    // }else if (isa<SEHFinallyStmt>(s)) {
    //   bool invalid;
    //   SEHFinallyStmt *statement = cast<SEHFinallyStmt>(s);
    //   CharSourceRange range = CharSourceRange::getTokenRange(statement->getBeginLoc(), statement->getEndLoc());
    //   StringRef str = Lexer::getSourceText(range, sm, langOptions, &invalid);
    //   stmtStr += "SEHFinallyStmt:" + str.str();
    // }else if (isa<SEHTryStmt>(s)) {
    //   bool invalid;
    //   SEHTryStmt *statement = cast<SEHTryStmt>(s);
    //   CharSourceRange range = CharSourceRange::getTokenRange(statement->getBeginLoc(), statement->getEndLoc());
    //   StringRef str = Lexer::getSourceText(range, sm, langOptions, &invalid);
    //   stmtStr += "SEHTryStmt:" + str.str();
    // }else if (isa<SEHLeaveStmt>(s)) {
    //   bool invalid;
    //   SEHLeaveStmt *statement = cast<SEHLeaveStmt>(s);
    //   CharSourceRange range = CharSourceRange::getTokenRange(statement->getBeginLoc(), statement->getEndLoc());
    //   StringRef str = Lexer::getSourceText(range, sm, langOptions, &invalid);
    //   stmtStr += "SEHLeaveStmt:" + str.str();
    // }else if (isa<CapturedStmt>(s)) {
    //   bool invalid;
    //   CapturedStmt *statement = cast<CapturedStmt>(s);
    //   CharSourceRange range = CharSourceRange::getTokenRange(statement->getBeginLoc(), statement->getEndLoc());
    //   StringRef str = Lexer::getSourceText(range, sm, langOptions, &invalid);
    //   stmtStr += "CapturedStmt:" + str.str();
    // }
    *FileStream << stmtStr;
    return true;
  }
  bool VisitDecl(Decl *d) {
    SourceManager &sm = TheRewriter.getSourceMgr();
    std::string declStr;
    StringRef FileName = "test.nim";
    std::error_code EC;
    auto FileStream = std::make_shared<llvm::raw_fd_ostream>(FileName, EC, llvm::sys::fs::F_Append);
    if (isa<EnumDecl>(d)) {
      bool invalid;
      EnumDecl *decl = cast<EnumDecl>(d);

      CharSourceRange range = CharSourceRange::getTokenRange(decl->getLocation());
      StringRef str = Lexer::getSourceText(range, sm, LangOptions(), &invalid);
      declStr += str.str();
    } else if (isa<FunctionDecl>(d)) {
      bool invalid;
      FunctionDecl *f = cast<FunctionDecl>(d);
      std::string functionStr;
    SourceManager &sm = TheRewriter.getSourceMgr();
    StringRef FileName = "test.nim";
    std::error_code EC;
    auto FileStream = std::make_shared<llvm::raw_fd_ostream>(FileName, EC, llvm::sys::fs::F_Append);
    if (EC) {
      llvm::errs() << "Could not open " << FileName << "\n";
      return false;
    }
    if (f->hasBody()) {
      std::string FuncName = f->getNameInfo().getName().getAsString();
      functionStr += "\nproc " + FuncName  + "*(";
      unsigned int nums = f->getNumParams();
      if (nums == 0) functionStr += ")";
      else {
        for(unsigned int i=0; i < nums; i++) {
          QualType unqualifiedOriginalType = f->getParamDecl(i)->getType().getUnqualifiedType();


          std::string typeStr = unqualifiedOriginalType.getAsString();
          if (TypeTable.count(typeStr)) {
            typeStr = TypeTable[typeStr];
          }
          
          if (isa<PointerType>(unqualifiedOriginalType)) {
            QualType originalPointeeType = unqualifiedOriginalType.getTypePtr()->getPointeeType();
            std::string unqualifiedOriginalPointeeTypeStr = originalPointeeType.getAsString();
            if (originalPointeeType->isStructureType() && unqualifiedOriginalPointeeTypeStr.find("struct ") != std::string::npos) {
              typeStr = "ptr " + unqualifiedOriginalPointeeTypeStr.substr(7, unqualifiedOriginalPointeeTypeStr.length());
            } else if (originalPointeeType->isVoidType()) {
              typeStr = "pointer";
            } else if (originalPointeeType.hasQualifiers()) {
              typeStr = "ptr " + originalPointeeType.getUnqualifiedType().getAsString();
            
            } else {
              if (TypeTable.count(unqualifiedOriginalPointeeTypeStr)) {
                unqualifiedOriginalPointeeTypeStr = TypeTable[unqualifiedOriginalPointeeTypeStr];
              }
              typeStr = "ptr " + unqualifiedOriginalPointeeTypeStr;
            }
          }
          
          std::string name = f->getParamDecl(i)->getName();
          if (i == nums - 1) {
            functionStr += name + ": " + typeStr + ")";
          } else {
            functionStr += name + ": " + typeStr + ",";
          }
        }
        QualType returnType = f->getReturnType();
        std::string returnTypeStr = returnType.getAsString();
        if (isa<PointerType>(returnType)) {
          auto originalPointeeType = returnType.getTypePtr()->getPointeeType();
          std::string returnTypeName = originalPointeeType.getAsString();
          if (originalPointeeType->isVoidType()) {
            returnTypeStr = " pointer";
          } else if (returnTypeName.find("const ") != std::string::npos){
              returnTypeStr = "ptr " + returnTypeName.substr(6, returnTypeName.length());
              if (returnTypeName == "const char") {
                  returnTypeStr = " string";
              }
          } else if (returnTypeName.find("struct ") != std::string::npos) {
              returnTypeStr = "ptr " + returnTypeName.substr(7, returnTypeName.length());

          }else {
            if (TypeTable.count(returnTypeName)) {
              returnTypeName = TypeTable[returnTypeName];
            }
            returnTypeStr = " ptr " + returnTypeName;
          }
        } else if(returnTypeStr == "void") {
            returnTypeStr = "";
        } else if (TypeTable.count(returnTypeStr)) {
            returnTypeStr = TypeTable[returnTypeStr];
        }
        if (returnTypeStr != "") {
            functionStr += ":" + returnTypeStr + " = \n";
        }
      }
    }
    *FileStream << functionStr;
    return true;
    }
    *FileStream << declStr;
  }
private:
  Rewriter &TheRewriter;
};

class MyASTConsumer : public ASTConsumer {
public:
  MyASTConsumer(Rewriter &R) : Visitor(R) {}
  bool HandleTopLevelDecl(DeclGroupRef DR) override {
    // StringRef FileName = "ast.c";
    // std::error_code EC;
    // llvm::raw_fd_ostream FileStream(FileName, EC, llvm::sys::fs::F_Append);
    for (DeclGroupRef::iterator b = DR.begin(), e = DR.end(); b != e; ++b) {
      Visitor.TraverseDecl(*b);
      // (*b)->dump(FileStream, true);
      // (*b)->print(FileStream, 2, true);
    }
    return true;
  }

private:
  MyASTVisitor Visitor;
};

class MyFrontendAction : public ASTFrontendAction {
public:
  MyFrontendAction() {}
  void EndSourceFileAction() override {
    StringRef FileName = "test2.nim";
    std::error_code EC;
    SourceManager &SM = TheRewriter.getSourceMgr();
    auto FileStream = std::make_shared<llvm::raw_fd_ostream>(FileName, EC, llvm::sys::fs::F_Append);

    TheRewriter.getEditBuffer(SM.getMainFileID()).write(*FileStream);
  }

  std::unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance &CI,
                                                 StringRef file) override {
    TheRewriter.setSourceMgr(CI.getSourceManager(), CI.getLangOpts());
    return llvm::make_unique<MyASTConsumer>(TheRewriter);
  }

private:
  Rewriter TheRewriter;
};

int main(int argc, const char **argv) {
  CommonOptionsParser op(argc, argv, ToolingSampleCategory);
  ClangTool Tool(op.getCompilations(), op.getSourcePathList());
  return Tool.run(newFrontendActionFactory<MyFrontendAction>().get());
}
