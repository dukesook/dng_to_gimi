#include <iostream>
#include <libraw/libraw.h> // sudo apt install libraw-dev

using namespace std;

ushort *get_dng_data(const char *filename, int &width, int &height, string &colorFilterPattern) {
  LibRaw rawProcessor;
  int ret = rawProcessor.open_file(filename);
  if (ret != LIBRAW_SUCCESS) {
    cerr << "Failed to open file: " << libraw_strerror(ret) << endl;
    return nullptr;
  }

  ret = rawProcessor.unpack();
  if (ret != LIBRAW_SUCCESS) {
    cerr << "Failed to unpack raw data: " << libraw_strerror(ret) << endl;
    return nullptr;
  }

  ushort *rawData = rawProcessor.imgdata.rawdata.raw_image;
  if (!rawData) {
    cerr << "raw_image is null (may not be Bayer format)." << endl;
    return nullptr;
  }

  width = rawProcessor.imgdata.sizes.raw_width;
  height = rawProcessor.imgdata.sizes.raw_height;
  colorFilterPattern = rawProcessor.imgdata.idata.cdesc; // e.g., "RGGB"

  size_t size = width * height * sizeof(ushort);
  ushort *copied = new ushort[width * height];
  memcpy(copied, rawData, size);

  rawProcessor.recycle(); // Free LibRaw internals, not your copy
  return copied;
}

int main(int argc, char *argv[]) {

  const char *filename = "baseball.dng";
  int width, height;
  string colorFilterPattern;
  ushort *rawData = get_dng_data(filename, width, height, colorFilterPattern);
  if (!rawData) {
    cerr << "Failed to get DNG data." << endl;
    return 1;
  }

  cout << "Image dimensions: "
       << width << " x "
       << height << endl;

  cout << "Color filter pattern: " << colorFilterPattern << endl;

  cout << "First pixel value: " << rawData[0] << endl;

  if (rawData) {
    delete[] rawData; // Free the copied data
  }

  return 0;
}