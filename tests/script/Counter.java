public final class Counter extends Object {

	public static int value = 0;

	public static synchronized void SetCounter(int value) {
		Counter.value = value;
	}

	public static synchronized void IncrementCounter() {
		Counter.value++;
	}

	public static synchronized int GetCounter() {
		return Counter.value;
	}
}
