#include <ctype.h>
#include <map>
#include <iostream>

// SPI - Simple Pascal Interpreter
enum
{
    INTEGER = "INTEGER",
    PLUS = "PLUS",
    MINUS = "MINUS",
    MUL = "MUL",
    DIV = "DIV",
    LPAREN = "LPAREN",
    RPAREN = "RPAREN",
    ID = "ID",
    ASSIGN = "ASSIGN",
    BEGIN = "BEGIN",
    END = "END",
    SEMI = "SEMI",
    DOT = "DOT",
    EOF = "EOF"
};

/*

    Lexer

*/

template <typename T>
class Token
{
  public:
    Token(T type, std::string value) : type(type), value(value) {}
    inline std::string str(){return "Token(" + std::to_string(type) + ", " + std::to_string(value) + ")"};
    inline std::string Type() { return type; }
    inline T Value() { return value; }
    inline SetType(std::string type) { this.type = type; }
    inline SetValue(T value) { this.value = value; }

  private:
    U type;
    T value;
};

map<std::string, Token> RESERVED_KEYWORDS;
RESERVED_KEYWORDS.insert(pair<std::string, Token>(BEGIN, Token(BEGIN, BEGIN<std::string>)));
RESERVED_KEYWORDS.insert(pair<std::string, Token>(END, Token(END, END<std::string>)));

class Lexer
{
  public:
    Lexer(std::string text) : text(text) {}
    inline void error() { throw "Invalid character"; }

    inline void advance()
    {
        pos++;
        if (pos >= text.length())
            currentChar = '\0';
        else
            currentChar = text[pos];
    }

    inline char peek()
    {
        int peekPos = pos + 1;
        if (peekPos >= text.length())
            return '\0';
        else
            return text[peekPos];
    }

    inline void skipWhitespace()
    {
        while (currentChar != '\0' && isspace(currentChar))
            advance();
    }

    // return a multidigit integer consumed from the input
    inline int integer()
    {
        std::string result = "";
        while (currentChar != '\0' && isdigit(currentChar))
        {
            result += currentChar;
            advance();
        }
        return atoi(result.c_str());
    }

    // handle identifiers and reserved keywords
    inline Token _id()
    {
        std::string result = "";
        Token token;
        while (currentChar != '\0' && isalnum(currentChar))
        {
            result += currentChar;
            advance();
        }
        token = RESERVED_KEYWORDS[result];
        return token;
    }

    inline std::string getNextToken()
    {
        /*
        Lexical analyzer,
        break a sentence apart into tokens one at a time
        */

        while (currentChar != '\0')
        {
            if (isspace(currentChar))
            {
                skipWhitespace();
                continue;
            }
            if (isalpha(currentChar))
                return _id();

            if (isdigit(currentChar))
                return Token(INTEGER, integer());

            switch (currentChar)
            {
            case ':':
                if (peek() == '=')
                {
                    advance();
                    advance();
                    return Token(ASSIGN, ":=");
                }
                else
                    break;
            case ';':
                advance();
                advance();
                return Token(SEMI, ";");
            case '+':
                advance();
                return Token(PLUS, "+");
            case '-':
                advance();
                return Token(MINUS, "-");
            case '*':
                advance();
                return Token(MUL, "*");
            case '/':
                advance();
                return Token(DIV, "/");
            case '(':
                advance();
                return Token(LPAREN, "(");
            case ')':
                advance();
                return Token(RPAREN, ")");
            case '.':
                advance();
                return Token(DOT, ".");
            }

            error();
        } // end while(currentChar != '\0')

        return Token(EOF, '\0');
    } // end getNextToken()

  private:
    int pos = 0;
    char currentChar = text[pos];
} // end class Lexer

/*

    Parser

*/

class AST{};

