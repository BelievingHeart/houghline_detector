#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <string>
static cv::Mat color_image, output_image;
template <typename T> void increment(T &v, T amount, const char *var_name) {
  v += amount;
  cv::putText(color_image,
              std::string(var_name) + " increments by " +
                  std::to_string(amount),
              cv::Point2i(50, 50), cv::FONT_HERSHEY_SIMPLEX, 1,
              cv::Scalar(255, 0, 0), 3);
}

int main(int argc, char **argv) {
  cv::Mat canny;

  cv::CommandLineParser parser(
      argc, argv,
      "{help h ? | | Arg_1: a grayscale image\nArg_2: 1=houghline 2=houghlineP}"
      "{@image|<none>|}"
      "{@hough_type|<none>|}");
  //    cv::Mat input_image = cv::imread(parser.get<cv::String>("@image"),
  //    cv::IMREAD_GRAYSCALE);
  cv::Mat input_image = cv::imread("/home/afterburner/Pictures/hough_lines.png",
                                   cv::IMREAD_GRAYSCALE);
  const int hough_type = 1;
  //    const int hough_type = parser.get<int>("@hough_type");
  if (input_image.empty()) {
    std::cout << "Failed to load image: " << argv[1] << '\n';
    return 1;
  }
  cv::Canny(input_image, canny, 50, 200, 3);

  const char *winName = "hough lines";

  double rho = 1.0;
  double theta = CV_PI / 180.0;
  int threshold = 150;
  const double eps = CV_PI / 1000.0;
  if (hough_type == 1) {
    std::cout << "Increase decrease rho:        q, w\n"
                 "Increase decrease theta:      e, r\n"
                 "Increase decrease threshold:  t, y\n\n";
    while (true) {
      cv::cvtColor(input_image, color_image, cv::COLOR_GRAY2BGR);
      cv::cvtColor(input_image, output_image, cv::COLOR_GRAY2BGR);
      std::vector<cv::Vec2f> lines;
      cv::HoughLines(canny, lines, rho, theta, threshold, 0, 0);
      for (const auto &line : lines) {
        double rho_ = line[0], theta_ = line[1];
        cv::Point pt1, pt2;
        double a = cos(theta_), b = sin(theta_);
        double x0 = a * rho_, y0 = b * rho_;
        pt1.x = cvRound(x0 + 1000 * (-b));
        pt1.y = cvRound(y0 + 1000 * (a));
        pt2.x = cvRound(x0 - 1000 * (-b));
        pt2.y = cvRound(y0 - 1000 * (a));
        cv::line(output_image, pt1, pt2, cv::Scalar(0, 0, 255), 2, cv::LINE_AA);
      }
      cv::imshow(winName, output_image);
      char key = static_cast<char>(cv::waitKey(0));
      if (key == 'q') {
        increment(rho, 0.2, "rho");
      }
      if (key == 'w') {
        if (rho > 0.2 + eps) {
          increment(rho, -0.2, "rho");
        }
      }
      if (key == 'e') {
        increment(theta, CV_PI / 180, "theta");
      }
      if (key == 'r') {
        if (theta > CV_PI / 180 + eps) {
          increment(theta, -CV_PI / 180, "theta");
        }
      }
      if (key == 't') {
        if (threshold < 255 - eps) {
          increment(threshold, 3, "treshold");
        }
      }
      if (key == 'y') {
        if (threshold > 3) {
          increment(threshold, -3, "treshold");
        }
      }
      if (static_cast<int>(key) == 27) {
        break;
      }
      if (key == 'i') {
        std::cout << std::string("current rho: ") + std::to_string(rho) + "\n" +
                         "current theta: " + std::to_string(theta) +
                         "\n"
                         "current theta: " +
                         std::to_string(theta) + "\n";
      }
      cv::imshow("Origin", color_image);
    }
  }
  return 0;
}