class CsvUtils {
public:

  static String* parseCSVToArray(const String& csv) {
    const int maxItems = 10;  // Adjust based on your maximum expected number of items
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