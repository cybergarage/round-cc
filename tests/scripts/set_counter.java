import java.lang.Integer;

public class set_counter extends Object {

  public set_counter() {
  }

  public String run(String params) {
    try {
      int value = Integer.parseInt(params);
      Counter.SetValue(value);
    } catch (Exception e) {}

    return String.valueOf(Counter.GetValue());
  }
}
