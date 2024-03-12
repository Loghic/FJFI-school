
from plain_output import Output

class Product (Output) :

   def send_while_stat (self, param) :
      inx = 1
      self.send ("while")
      self.send ("(")
      value = param [inx]
      inx = inx + 1
      self.send_expr (value)
      self.send (")")
      value = param [inx]
      inx = inx + 1
      self.send_stat (value)

   def send_if_stat (self, param) :
      inx = 1
      self.send ("if")
      self.send ("(")
      value = param [inx]
      inx = inx + 1
      self.send_expr (value)
      self.send (")")
      value = param [inx]
      inx = inx + 1
      self.send_stat (value)
      cont = param [inx]
      inx = inx + 1
      if cont :
         self.send ("else")
         value = param [inx]
         inx = inx + 1
         self.send_stat (value)

   def send_compound_stat (self, param) :
      inx = 1
      self.send ("{")
      cont = param [inx]
      inx = inx + 1
      while cont :
         value = param [inx]
         inx = inx + 1
         self.send_stat (value)
         cont = param [inx]
         inx = inx + 1
      self.send ("}")

   def send_simple_stat (self, param) :
      inx = 1
      value = param [inx]
      inx = inx + 1
      self.send_expr (value)
      self.send (";")

   def send_empty_stat (self, param) :
      inx = 1
      self.send (";")

   def send_stat (self, param) :
      inx = 1
      alt = param [inx]
      inx = inx + 1
      if alt == 0 :
         value = param [inx]
         inx = inx + 1
         self.send_while_stat (value)
      elif alt == 1 :
         value = param [inx]
         inx = inx + 1
         self.send_if_stat (value)
      elif alt == 2 :
         value = param [inx]
         inx = inx + 1
         self.send_compound_stat (value)
      elif alt == 3 :
         value = param [inx]
         inx = inx + 1
         self.send_simple_stat (value)
      elif alt == 4 :
         value = param [inx]
         inx = inx + 1
         self.send_empty_stat (value)

   def send_simple_expr (self, param) :
      inx = 1
      alt = param [inx]
      inx = inx + 1
      if alt == 0 :
         value = param [inx]
         inx = inx + 1
         self.send (value)
      elif alt == 1 :
         value = param [inx]
         inx = inx + 1
         self.send (value)
      elif alt == 2 :
         self.send ("(")
         value = param [inx]
         inx = inx + 1
         self.send_expr (value)
         self.send (")")

   def send_mult_expr (self, param) :
      inx = 1
      value = param [inx]
      inx = inx + 1
      self.send_simple_expr (value)
      cont = param [inx]
      inx = inx + 1
      while cont :
         alt = param [inx]
         inx = inx + 1
         if alt == 0 :
            self.send ("*")
         elif alt == 1 :
            self.send ("/")
         value = param [inx]
         inx = inx + 1
         self.send_simple_expr (value)
         cont = param [inx]
         inx = inx + 1

   def send_add_expr (self, param) :
      inx = 1
      value = param [inx]
      inx = inx + 1
      self.send_mult_expr (value)
      cont = param [inx]
      inx = inx + 1
      while cont :
         alt = param [inx]
         inx = inx + 1
         if alt == 0 :
            self.send ("+")
         elif alt == 1 :
            self.send ("-")
         value = param [inx]
         inx = inx + 1
         self.send_mult_expr (value)
         cont = param [inx]
         inx = inx + 1

   def send_expr (self, param) :
      inx = 1
      value = param [inx]
      inx = inx + 1
      self.send_add_expr (value)
      cont = param [inx]
      inx = inx + 1
      if cont :
         self.send ("=")
         value = param [inx]
         inx = inx + 1
         self.send_expr (value)

   def send_program (self, param) :
      inx = 1
      value = param [inx]
      inx = inx + 1
      self.send_stat (value)

