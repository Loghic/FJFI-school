// if not in current namespace I do not not want to use the prefix of namespace
using OtherNamespace;
using someNameSpace = InsideNamespace; // alias for namespace

using Konzola = System.Console; // alias for type

namespace Namespaces
{
  internal class Program
  {
    static void Main(string[] args)
    {
      TestInNamespace t = new TestInNamespace();

      TestOtherNamespace to = new TestOtherNamespace();

      InsideNamespace.TestInNamespace ito = new InsideNamespace.TestInNamespace();

      someNameSpace.TestInNamespace qq = new someNameSpace.TestInNamespace();

      Console.WriteLine("Hello world!");

      Konzola.WriteLine("Test of Konzola");
    }
  }
}

namespace Namespaces
{
  class TestInNamespace
  {
    public TestInNamespace() {Console.WriteLine("Namespaces");}
  }

  namespace InsideNamespace
  {
    class TestInNamespace
    {
    public TestInNamespace() {Console.WriteLine("InsideNamespace");}
    }
  }
}

namespace OtherNamespace
{
  class TestOtherNamespace
  {
    public TestOtherNamespace() {Console.WriteLine("OtherNamespace");}
  }
}
