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
    if (isa<IfStmt>(s)) {
      IfStmt *IfStatement = cast<IfStmt>(s);
      Stmt *Then = IfStatement->getThen();
      Expr *cond = IfStatement->getCond();
      bool invalid;
      SourceManager &sm = TheRewriter.getSourceMgr();
      CharSourceRange conditionRange = CharSourceRange::getTokenRange(cond->getBeginLoc(), cond->getEndLoc());
      StringRef str = Lexer::getSourceText(conditionRange, sm, LangOptions(), &invalid);

      Stmt *Else = IfStatement->getElse();
      if (Else)
        TheRewriter.InsertText(Else->getBeginLoc(), "// the 'else' part\n", true, true);
    } else if (isa<AttributedStmt>(s)) {
      bool invalid;
      AttributedStmt *AttributedStatement = cast<AttributedStmt>(s);
      CharSourceRange AttributedRange = CharSourceRange::getTokenRange(AttributedStatement->getBeginLoc(), AttributedStatement->getEndLoc());
      StringRef str = Lexer::getSourceText(AttributedRange, sm, LangOptions(), &invalid);
      // *FileStream << str;


    } else if (isa<LabelStmt>(s)) {
      bool invalid;

      LabelStmt *statement = cast<LabelStmt>(s);
      CharSourceRange range = CharSourceRange::getTokenRange(statement->getBeginLoc(), statement->getEndLoc());
      StringRef str = Lexer::getSourceText(range, sm, LangOptions(), &invalid);
      // *FileStream << str;
    } else if (isa<ValueStmt>(s)) {
      bool invalid;

      ValueStmt *statement = cast<ValueStmt>(s);
      CharSourceRange range = CharSourceRange::getTokenRange(statement->getBeginLoc(), statement->getEndLoc());
      StringRef str = Lexer::getSourceText(range, sm, LangOptions(), &invalid);
      // *FileStream << str;
    } else if (isa<DefaultStmt>(s)) {
      bool invalid;

      DefaultStmt *statement = cast<DefaultStmt>(s);
      CharSourceRange range = CharSourceRange::getTokenRange(statement->getBeginLoc(), statement->getEndLoc());
      StringRef str = Lexer::getSourceText(range, sm, LangOptions(), &invalid);
      // *FileStream << str ;
    } else if (isa<CaseStmt>(s)) {
      bool invalid;

      CaseStmt *statement = cast<CaseStmt>(s);
      CharSourceRange range = CharSourceRange::getTokenRange(statement->getBeginLoc(), statement->getEndLoc());
      StringRef str = Lexer::getSourceText(range, sm, LangOptions(), &invalid);
      // *FileStream << str ;
    } else if (isa<SwitchCase>(s)) {
      bool invalid;

      SwitchCase *statement = cast<SwitchCase>(s);
      CharSourceRange range = CharSourceRange::getTokenRange(statement->getBeginLoc(), statement->getEndLoc());
      StringRef str = Lexer::getSourceText(range, sm, LangOptions(), &invalid);
      // *FileStream << str ;
    } else if (isa<CompoundStmt>(s)) {
      bool invalid;

      CompoundStmt *statement = cast<CompoundStmt>(s);
      CharSourceRange range = CharSourceRange::getTokenRange(statement->getBeginLoc(), statement->getEndLoc());
      StringRef str = Lexer::getSourceText(range, sm, LangOptions(), &invalid);
      // *FileStream << str ;
    } else if (isa<NullStmt>(s)) {
      bool invalid;

      NullStmt *statement = cast<NullStmt>(s);
      CharSourceRange range = CharSourceRange::getTokenRange(statement->getBeginLoc(), statement->getEndLoc());
      StringRef str = Lexer::getSourceText(range, sm, LangOptions(), &invalid);
      // *FileStream << str ;

    } else if (isa<DeclStmt>(s)) {
      bool invalid;

      DeclStmt *statement = cast<DeclStmt>(s);
      CharSourceRange range = CharSourceRange::getTokenRange(statement->getBeginLoc(), statement->getEndLoc());
      StringRef str = Lexer::getSourceText(range, sm, LangOptions(), &invalid);
      // *FileStream << str ;

    } else if (isa<SwitchStmt>(s)) {
      bool invalid;

      SwitchStmt *statement = cast<SwitchStmt>(s);
      CharSourceRange range = CharSourceRange::getTokenRange(statement->getBeginLoc(), statement->getEndLoc());
      StringRef str = Lexer::getSourceText(range, sm, LangOptions(), &invalid);
      // *FileStream << str ;

    } else if (isa<WhileStmt>(s)) {
      bool invalid;

      WhileStmt *statement = cast<WhileStmt>(s);
      CharSourceRange range = CharSourceRange::getTokenRange(statement->getBeginLoc(), statement->getEndLoc());
      StringRef str = Lexer::getSourceText(range, sm, LangOptions(), &invalid);
      // *FileStream << str ;
    } else if (isa<DoStmt>(s)) {
      bool invalid;

      DoStmt *statement = cast<DoStmt>(s);
      CharSourceRange range = CharSourceRange::getTokenRange(statement->getBeginLoc(), statement->getEndLoc());
      StringRef str = Lexer::getSourceText(range, sm, LangOptions(), &invalid);
      // *FileStream << str ;

    } else if (isa<ForStmt>(s)) {
      bool invalid;

      ForStmt *statement = cast<ForStmt>(s);
      CharSourceRange range = CharSourceRange::getTokenRange(statement->getBeginLoc(), statement->getEndLoc());
      StringRef str = Lexer::getSourceText(range, sm, LangOptions(), &invalid);
      // *FileStream << str ;

    } else if (isa<GotoStmt>(s)) {
      bool invalid;

      GotoStmt *statement = cast<GotoStmt>(s);
      CharSourceRange range = CharSourceRange::getTokenRange(statement->getBeginLoc(), statement->getEndLoc());
      StringRef str = Lexer::getSourceText(range, sm, LangOptions(), &invalid);
      // *FileStream << str ;


    }else if (isa<IndirectGotoStmt>(s)) {
      bool invalid;

      IndirectGotoStmt *statement = cast<IndirectGotoStmt>(s);
      CharSourceRange range = CharSourceRange::getTokenRange(statement->getBeginLoc(), statement->getEndLoc());
      StringRef str = Lexer::getSourceText(range, sm, LangOptions(), &invalid);
      // *FileStream << str ;

    }else if (isa<ContinueStmt>(s)) {
      bool invalid;

      ContinueStmt *statement = cast<ContinueStmt>(s);
      CharSourceRange range = CharSourceRange::getTokenRange(statement->getBeginLoc(), statement->getEndLoc());
      StringRef str = Lexer::getSourceText(range, sm, LangOptions(), &invalid);
      // *FileStream << str ;


    }else if (isa<BreakStmt>(s)) {
      bool invalid;

      BreakStmt *statement = cast<BreakStmt>(s);
      CharSourceRange range = CharSourceRange::getTokenRange(statement->getBeginLoc(), statement->getEndLoc());
      StringRef str = Lexer::getSourceText(range, sm, LangOptions(), &invalid);
      // *FileStream << str ;

    }else if (isa<ReturnStmt>(s)) {
      bool invalid;

      ReturnStmt *statement = cast<ReturnStmt>(s);
      CharSourceRange range = CharSourceRange::getTokenRange(statement->getBeginLoc(), statement->getEndLoc());
      StringRef str = Lexer::getSourceText(range, sm, LangOptions(), &invalid);
      // *FileStream << str ;

    }else if (isa<AsmStmt>(s)) {
      bool invalid;

      AsmStmt *statement = cast<AsmStmt>(s);
      CharSourceRange range = CharSourceRange::getTokenRange(statement->getBeginLoc(), statement->getEndLoc());
      StringRef str = Lexer::getSourceText(range, sm, LangOptions(), &invalid);
      // *FileStream << str << "\n";

    }else if (isa<GCCAsmStmt>(s)) {
      bool invalid;

      AsmStmt *statement = cast<AsmStmt>(s);
      CharSourceRange range = CharSourceRange::getTokenRange(statement->getBeginLoc(), statement->getEndLoc());
      StringRef str = Lexer::getSourceText(range, sm, LangOptions(), &invalid);
      // *FileStream << str ;

    }else if (isa<MSAsmStmt>(s)) {
      bool invalid;

      MSAsmStmt *statement = cast<MSAsmStmt>(s);
      CharSourceRange range = CharSourceRange::getTokenRange(statement->getBeginLoc(), statement->getEndLoc());
      StringRef str = Lexer::getSourceText(range, sm, LangOptions(), &invalid);
      // *FileStream << str ;


    }else if (isa<SEHExceptStmt>(s)) {
      bool invalid;

      SEHExceptStmt *statement = cast<SEHExceptStmt>(s);
      CharSourceRange range = CharSourceRange::getTokenRange(statement->getBeginLoc(), statement->getEndLoc());
      StringRef str = Lexer::getSourceText(range, sm, LangOptions(), &invalid);
      // *FileStream << str << "\n";

    }else if (isa<SEHFinallyStmt>(s)) {
      bool invalid;

      SEHFinallyStmt *statement = cast<SEHFinallyStmt>(s);
      CharSourceRange range = CharSourceRange::getTokenRange(statement->getBeginLoc(), statement->getEndLoc());
      StringRef str = Lexer::getSourceText(range, sm, LangOptions(), &invalid);
      // *FileStream << str ;

    }else if (isa<SEHTryStmt>(s)) {
      bool invalid;

      SEHTryStmt *statement = cast<SEHTryStmt>(s);
      CharSourceRange range = CharSourceRange::getTokenRange(statement->getBeginLoc(), statement->getEndLoc());
      StringRef str = Lexer::getSourceText(range, sm, LangOptions(), &invalid);
      // *FileStream << str ;

    }else if (isa<SEHLeaveStmt>(s)) {
      bool invalid;

      SEHLeaveStmt *statement = cast<SEHLeaveStmt>(s);
      CharSourceRange range = CharSourceRange::getTokenRange(statement->getBeginLoc(), statement->getEndLoc());
      StringRef str = Lexer::getSourceText(range, sm, LangOptions(), &invalid);
      // *FileStream << str ;

    }else if (isa<CapturedStmt>(s)) {
      bool invalid;

      CapturedStmt *statement = cast<CapturedStmt>(s);
      CharSourceRange range = CharSourceRange::getTokenRange(statement->getBeginLoc(), statement->getEndLoc());
      StringRef str = Lexer::getSourceText(range, sm, LangOptions(), &invalid);
      // *FileStream << str ;
    }


    return true;
  }

  bool VisitFunctionDecl(FunctionDecl *f) {
    if (f->hasBody()) {
      QualType QT = f->getReturnType();
      std::string TypeStr = QT.getAsString();

      DeclarationName DeclName = f->getNameInfo().getName();
      std::string FuncName = DeclName.getAsString();

      SourceManager &sm = TheRewriter.getSourceMgr();
      StringRef FileName = "test.nim";
      std::error_code EC;
      auto FileStream = std::make_shared<llvm::raw_fd_ostream>(FileName, EC, llvm::sys::fs::F_Append);
      if (EC) {
        llvm::errs() << "Could not open " << FileName << "\n";
      // std::stringstream SSBefore;
      // SSBefore << "// Begin function " << FuncName << " returning " << TypeStr << "\n";
      // SourceLocation ST = f->getSourceRange().getBegin();
      // TheRewriter.InsertText(ST, SSBefore.str(), true, true);

      // std::stringstream SSAfter;
      // SSAfter << "\n// End function " << FuncName;
      // ST = FuncBody->getEndLoc().getLocWithOffset(1);
      // TheRewriter.InsertText(ST, SSAfter.str(), true, true);
      }else{
        *FileStream << "\nproc " + FuncName  + "(";
        unsigned int nums = f->getNumParams();
        for(unsigned int i=0; i < nums; i++) {
          std::string type = f->getParamDecl(i)->getType().getAsString();
          std::string name = f->getParamDecl(i)->getName();
          if (i == nums - 1) {
            *FileStream << name + ":" + type + ")";
          } else {
            *FileStream << name + ":" + type + ",";
          }
        }
        Stmt *body = f->getBody();
        CharSourceRange range = CharSourceRange::getTokenRange(body->getBeginLoc().getLocWithOffset(1), body->getEndLoc().getLocWithOffset(-1));
        bool invalid;

        StringRef bodyStr = Lexer::getSourceText(range, sm, LangOptions(), &invalid);
        if (bodyStr != "") {
          *FileStream << "=" + bodyStr;
        }
      }
    }
    return true;
  }

private:
  Rewriter &TheRewriter;
};

class MyASTConsumer : public ASTConsumer {
public:
  MyASTConsumer(Rewriter &R) : Visitor(R) {}

  bool HandleTopLevelDecl(DeclGroupRef DR) override {
    StringRef FileName = "ast.c";
    std::error_code EC;

    llvm::raw_fd_ostream FileStream(FileName, EC, llvm::sys::fs::F_Append);

    // for (DeclGroupRef::iterator b = DR.begin(), e = DR.end(); b != e; ++b) {
    //   Visitor.TraverseDecl(*b);
    //   (*b)->dump(FileStream, true);
    //   (*b)->print(FileStream, 2, true);
    // }
    return true;
  }

private:
  MyASTVisitor Visitor;
};

class MyFrontendAction : public ASTFrontendAction {
public:
  MyFrontendAction() {}
  void EndSourceFileAction() override {
    SourceManager &SM = TheRewriter.getSourceMgr();

    // TheRewriter.getEditBuffer(SM.getMainFileID()).write(llvm::outs());
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
