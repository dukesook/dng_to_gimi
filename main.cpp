#include <iostream>
#include <libraw/libraw.h> // sudo apt install libraw-dev

using namespace std;

int main(int argc, char *argv[]) {

  const char *filename = "baseball.dng";
  LibRaw rawProcessor;

  int ret = rawProcessor.open_file(filename);
  if (ret != LIBRAW_SUCCESS) {
    cerr << "Failed to open file: " << libraw_strerror(ret) << endl;
    return 1;
  }

  ret = rawProcessor.unpack();
  if (ret != LIBRAW_SUCCESS) {
    cerr << "Failed to unpack raw data: " << libraw_strerror(ret) << endl;
    return 1;
  }

  cout << "Image dimensions: "
       << rawProcessor.imgdata.sizes.width << " x "
       << rawProcessor.imgdata.sizes.height << endl;

  cout << "Color filter pattern: " << rawProcessor.imgdata.idata.cdesc << endl;

  ushort *rawData = rawProcessor.imgdata.rawdata.raw_image;
  if (!rawData) {
    cerr << "raw_image is null (may not be Bayer format)." << endl;
    return 1;
  }

  cout << "First pixel value: " << rawData[0] << endl;

  rawProcessor.recycle();
  return 0;
}