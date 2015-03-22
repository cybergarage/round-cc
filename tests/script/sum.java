import java.lang.Integer;

public class sum extends Object {
  public sum() {
  }
  public String processMessage(String params) {
    String []param = new String[0];
    try {
    	param = params.split("[^0-9]");
    } catch (Exception e) {}
    int sum = 0;
    for (int n=0; n<param.length; n++) {
      try {
        sum += Integer.parseInt(param[n]);
      } catch (Exception e) {}
    }
    return String.valueOf(sum);
  }
}
