import java.lang.Integer;

public class set_counter extends Object {

  public set_counter() {
  }

  public String processMessage(String params) {
    try {
      int value = Integer.parseInt(params);
      Counter.value = value;
    } catch (Exception e) {}

    return String.valueOf(Counter.value);
  }
}
