import java.lang.Integer;

public class get_counter extends Object {

  public get_counter() {
  }

  public String processMessage(String params) {
    return String.valueOf(Counter.value);
  }
}
