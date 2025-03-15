cmake_minimum_required(VERSION 3.27)
project(8_7_58rewrite)

set(CMAKE_CXX_STANDARD 17)

add_executable(8_7_58rewrite main.cpp
        Deque.h
        Lexer.h
        Token.h
        Expression.h
        ExpressionNode.h
        Parser.h
        PostFix.h
        ExpressionTreePrint.h
        ExpressionTreePrint.cpp
        ConDec.cpp
        Parser.cpp
        PostFix.cpp
        Expression.cpp
)
