import java.lang.reflect.Field;

public class HelloWorld {

    public static void main(String[] args) throws Exception {
        Field field = String.class.getDeclaredField("value");
        field.setAccessible(true);
        char[] chars = (char[]) field.song_node_get("Hello, World");
        chars[0] = 'K';
        System.out.println("Hello, World");
    }
    
}