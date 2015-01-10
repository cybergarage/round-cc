import java.lang.Integer;

public class inc_counter extends Object {

  public inc_counter() {
  }

  public String processMessage(String params) {
    Counter.value++;
    return String.valueOf(Counter.value);
  }
}
