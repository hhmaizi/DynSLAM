#ifndef DYNSLAM_PRECOMPUTEDDEPTHPROVIDER_H
#define DYNSLAM_PRECOMPUTEDDEPTHPROVIDER_H

#include <string>

#include "DepthProvider.h"

namespace dynslam {

extern const std::string kDispNetName;
extern const std::string kPrecomputedElas;

/// \brief Reads precomputed disparity (default) or depth maps from a folder.
/// The depth maps are expected to be grayscale, and in short 16-bit or float 32-bit format.
class PrecomputedDepthProvider : public DepthProvider {
 public:
  virtual ~PrecomputedDepthProvider() {}

  PrecomputedDepthProvider(const std::string &folder,
                         const std::string &fname_format,
                         bool input_is_depth = false)
      : DepthProvider(input_is_depth),
        folder(folder),
        fname_format(fname_format),
        frame_idx(0) {}

  virtual void DisparityMapFromStereo(const cv::Mat &left,
                                      const cv::Mat &right,
                                      cv::Mat &out_disparity) override;

  virtual float DepthFromDisparity(const float disparity_px,
                                   const StereoCalibration &calibration) override;

  const std::string& GetName() const override;

 private:
  std::string folder;
  /// \brief The printf-style format of the frame filenames, such as "frame-%04d.png" for frames
  /// which are called "frame-0000.png"-"frame-9999.png".
  std::string fname_format;
  int frame_idx;
};

} // namespace dynslam

#endif //DYNSLAM_PRECOMPUTEDDEPTHPROVIDER_H
