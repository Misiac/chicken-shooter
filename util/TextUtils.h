#include "Config.h"

class TextUtils {
public:
  static String getSpecificLine(String text, int lineNumber) {
    int currentLine = 0;
    int startIndex = 0;
    int endIndex = 0;

    while (currentLine < lineNumber) {
      startIndex = text.indexOf('\n', startIndex) + 1;
      if (startIndex == 0)
        return "";
      currentLine++;
    }

    endIndex = text.indexOf('\n', startIndex);
    if (endIndex == -1) {
      endIndex = text.length();
    }

    return text.substring(startIndex, endIndex);
  }

  static String* parseCSVToArray(const String& csv) {
    const int maxItems = Config::MAX_PLAYERS;
    static String items[maxItems];
    int count = 0;

    int startIndex = 0;
    int commaIndex;
    while ((commaIndex = csv.indexOf(',', startIndex)) != -1 && count < maxItems) {
      items[count] = csv.substring(startIndex, commaIndex);
      items[count].trim();
      count++;
      startIndex = commaIndex + 1;
    }
    // Add the last item after the final comma (or the only item if there are no commas)
    if (count < maxItems) {
      items[count] = csv.substring(startIndex);
      items[count].trim();
      count++;
    }
    return items;
  }
};