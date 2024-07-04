class StringUtils {
public:
  static String getSpecificLine(String text, int lineNumber) {
    int currentLine = 0;
    int startIndex = 0;
    int endIndex = 0;

    while (currentLine <= lineNumber) {
      startIndex = endIndex;
      endIndex = text.indexOf('\n', startIndex + 1);

      if (endIndex == -1) {
        endIndex = text.length();
      }

      currentLine++;
    }

    return text.substring(startIndex, endIndex);
  }
};