
from plain_lexer import Lexer

class Parser (Lexer) :
   def parse_while_stat (self) :
      result = [ "while_stat" ]
      self.check ("while")
      self.check ("(")
      result.append (self.parse_expr ())
      self.check (")")
      result.append (self.parse_stat ())
      return result

   def parse_if_stat (self) :
      result = [ "if_stat" ]
      self.check ("if")
      self.check ("(")
      result.append (self.parse_expr ())
      self.check (")")
      result.append (self.parse_stat ())
      if self.tokenText == "else" :
         result.append (True)
         self.check ("else")
         result.append (self.parse_stat ())
      else :
         result.append (False)
      return result

   def parse_compound_stat (self) :
      result = [ "compound_stat" ]
      self.check ("{")
      while self.set_0 [self.token] :
         result.append (True)
         result.append (self.parse_stat ())
      result.append (False)
      self.check ("}")
      return result

   def parse_simple_stat (self) :
      result = [ "simple_stat" ]
      result.append (self.parse_expr ())
      self.check (";")
      return result

   def parse_empty_stat (self) :
      result = [ "empty_stat" ]
      self.check (";")
      return result

   def parse_stat (self) :
      result = [ "stat" ]
      if self.tokenText == "while" :
         result.append (0)
         result.append (self.parse_while_stat ())
      elif self.tokenText == "if" :
         result.append (1)
         result.append (self.parse_if_stat ())
      elif self.tokenText == "{" :
         result.append (2)
         result.append (self.parse_compound_stat ())
      elif self.token == self.identifier or self.token == self.number or self.tokenText == "(" :
         result.append (3)
         result.append (self.parse_simple_stat ())
      elif self.tokenText == ";" :
         result.append (4)
         result.append (self.parse_empty_stat ())
      else :
         self.error ("Unexpected token")
      return result

   def parse_simple_expr (self) :
      result = [ "simple_expr" ]
      if self.token == self.identifier :
         result.append (0)
         result.append (self.readIdentifier ())
      elif self.token == self.number :
         result.append (1)
         result.append (self.readNumber ())
      elif self.tokenText == "(" :
         result.append (2)
         self.check ("(")
         result.append (self.parse_expr ())
         self.check (")")
      else :
         self.error ("Unexpected token")
      return result

   def parse_mult_expr (self) :
      result = [ "mult_expr" ]
      result.append (self.parse_simple_expr ())
      while self.tokenText == "*" or self.tokenText == "/" :
         result.append (True)
         if self.tokenText == "*" :
            result.append (0)
            self.check ("*")
         elif self.tokenText == "/" :
            result.append (1)
            self.check ("/")
         else :
            self.error ("Unexpected token")
         result.append (self.parse_simple_expr ())
      result.append (False)
      return result

   def parse_add_expr (self) :
      result = [ "add_expr" ]
      result.append (self.parse_mult_expr ())
      while self.tokenText == "+" or self.tokenText == "-" :
         result.append (True)
         if self.tokenText == "+" :
            result.append (0)
            self.check ("+")
         elif self.tokenText == "-" :
            result.append (1)
            self.check ("-")
         else :
            self.error ("Unexpected token")
         result.append (self.parse_mult_expr ())
      result.append (False)
      return result

   def parse_expr (self) :
      result = [ "expr" ]
      result.append (self.parse_add_expr ())
      if self.tokenText == "=" :
         result.append (True)
         self.check ("=")
         result.append (self.parse_expr ())
      else :
         result.append (False)
      return result

   def parse_program (self) :
      result = [ "program" ]
      result.append (self.parse_stat ())
      return result

   def lookupKeyword (self) :
      s = self.tokenText
      n = len (s)
      if n == 2 :
         if s[0:2] == "if" :
            self.token = self.keyword_if
      elif n == 4 :
         if s[0:4] == "else" :
            self.token = self.keyword_else
      elif n == 5 :
         if s[0:5] == "while" :
            self.token = self.keyword_while

   def processSeparator (self) :
      if self.tokenText == '(' :
         self.token = 11
      if self.tokenText == ')' :
         self.token = 12
      if self.tokenText == '*' :
         self.token = 13
      if self.tokenText == '+' :
         self.token = 14
      if self.tokenText == '-' :
         self.token = 15
      if self.tokenText == '/' :
         self.token = 16
      if self.tokenText == ';' :
         self.token = 17
      if self.tokenText == '=' :
         self.token = 18
      if self.tokenText == '{' :
         self.token = 19
      if self.tokenText == '}' :
         self.token = 20
      if self.token == self.separator :
         self.error ("Unknown separator")

   def tokenToString (self, value) :
      if value == 0: return "<end of source text>"
      if value == 1: return "<identifier>"
      if value == 2: return "<number>"
      if value == 3: return "<real_number>"
      if value == 4: return "<character_literal>"
      if value == 5: return "<string_literal>"
      if value == 6: return "<unknown separator>"
      if value == 7: return "<end of line>"
      if value == 8: return "else"
      if value == 9: return "if"
      if value == 10: return "while"
      if value == 11: return "("
      if value == 12: return ")"
      if value == 13: return "*"
      if value == 14: return "+"
      if value == 15: return "-"
      if value == 16: return "/"
      if value == 17: return ";"
      if value == 18: return "="
      if value == 19: return "{"
      if value == 20: return "}"
      return "<unknown symbol>"

   def storeLocation (self, item) :
      item.src_line = self.tokenLineNum
      item.src_column = self.tokenColNum
      item.src_pos = self.tokenByteOfs
      item.src_end = self.charByteOfs

   def alloc (self, items) :
      result = [False] * 21
      for item in items :
         result [item] = True
      return result

   def __init__ (self) :
      super (Parser, self).__init__ ()

      # eos = 0
      # identifier = 1
      # number = 2
      # real_number = 3
      # character_literal = 4
      # string_literal = 5
      # separator = 6
      # end_of_line = 7
      self.keyword_else = 8
      self.keyword_if = 9
      self.keyword_while = 10
      # ( 11
      # ) 12
      # * 13
      # + 14
      # - 15
      # / 16
      # ; 17
      # = 18
      # { 19
      # } 20

      self.set_0 = self.alloc ([self.identifier, self.number, self.keyword_if, self.keyword_while, 11, 17, 19]) #  identifier  number  if  while  (  ;  {

