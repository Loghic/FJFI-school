namespace overloading
{
  internal class Complex
  {
    private double Re {get; set;}
    private double Im {get; set;}

    public Complex(double re, double im = 0)
    {
      Re = re;
      Im = im;
    }

    public Complex (Complex z)
    {
      Re = z.Re;
      Im = z.Im;
    }

    public static readonly Complex ZERO = new(0);
    public static readonly Complex I = new(0, 1);

    public static Complex operator+(Complex z)
    {
      return new Complex(z);
    }

    public static Complex operator-(Complex z)
    {
      return new Complex(-z.Re, -z.Im);
    }

    public static Complex operator+(Complex z, Complex w)
    {
      return new Complex(z.Re + w.Re, z.Im + w.Im);
    }

    public override string ToString()
    {
        return Re.ToString() + " + " +  Im.ToString() + ".i";
    }

    public void Deconstruct(out double re, out double im) => (re, im) = (Re, Im);

    public static implicit operator Complex((double re, double im) v) => new Complex(v.re, v.im);

    public static implicit operator Complex(double re) => new Complex(re);

    public static explicit operator double(Complex z)
    {
      if (z.Im != 0)
      {
        throw new ArgumentException("Nenulova imaginarni cast");
      }

      return z.Re;
    }

  }

}
