public class File implements Control
{
    public File(String text)
    {
        this.text = text;
    }

    @Override
    public void zkontroluj()
    {
        if (text == null){
//            System.out.println("Text is not provided");
            System.out.println("Text is not OKAY:/");
        }
    }

    @Override
    public void defaultControl()
    {
        System.out.println("Default control of file!");
    }

    private String text;
}
