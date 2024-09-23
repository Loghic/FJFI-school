import java.util.HashMap;

public class SudokuHelper {
    private HashMap<String, Integer> valueMap = new HashMap<>();

    public void addValue(String key, Integer value) {
        valueMap.put(key, value);
    }

    public Integer getValue(String key) {
        return valueMap.get(key);
    }

    public void removeValue(String key) {
        valueMap.remove(key);
    }

    public void clear() {
        valueMap.clear();
    }

    @Override
    public String toString() {
        return valueMap.toString();
    }
}
