class StringUtils {
public:
  static String getSpecificLine(String text, int lineNumber) {
    int currentLine = 0;
    int startIndex = 0;
    int endIndex = 0;

    while (currentLine < lineNumber) {
      startIndex = text.indexOf('\n', startIndex) + 1;
      if (startIndex == 0)  // If '\n' is not found
        return "";          // Return empty string if line number is out of range
      currentLine++;
    }

    endIndex = text.indexOf('\n', startIndex);
    if (endIndex == -1) {
      endIndex = text.length();
    }

    return text.substring(startIndex, endIndex);
  }
};