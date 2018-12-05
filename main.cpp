#include <cmath>                        // for cos, sin
#include <opencv2/core/cvdef.h>          // for CV_PI
#include <iostream>                      // for operator<<, cout, ostream
#include <opencv2/core/cvstd.hpp>        // for String
#include <opencv2/core/fast_math.hpp>    // for cvRound
#include <opencv2/core/mat.hpp>          // for Mat, MatExpr
#include <opencv2/core/utility.hpp>      // for CommandLineParser
#include "opencv2/highgui.hpp"           // for imshow, moveWindow, namedWindow
#include "opencv2/imgproc.hpp"           // for cvtColor, line, putText, COL...

static cv::Mat color_image, output_image;
int hough_type = 1;
double rho = 1.0;
double theta = CV_PI / 180.0;
double minLineLen = 50, maxLineGap = 50;
int threshold = 150;
const double eps = CV_PI / 1000.0;

void put_status(std::string var_name, double v, int height) {
  cv::putText(color_image,
              std::string("current ") + var_name + ":      " +
                  std::to_string(v),
              cv::Point2i(30, height), cv::FONT_HERSHEY_PLAIN, 1,
              cv::Scalar(255, 255, 255), 1);
}

template <typename T> void increment(T &v, T amount, const char *var_name) {
  v += amount;
  const std::string op = amount > 0 ? std::string(" increments by ")
                                    : std::string(" decrements by ");
  const T amount_ = amount > 0 ? amount : -amount;
  cv::putText(color_image, std::string(var_name) + op + std::to_string(amount_),
              cv::Point2i(30, 50), cv::FONT_HERSHEY_SIMPLEX, 0.5,
              cv::Scalar(255, 255, 255), 1);

  put_status("rho", rho, 70);
  put_status("theta", theta, 90);
  put_status("threshold", threshold, 110);
  if (hough_type != 1) {
    put_status("minLineLen", minLineLen, 130);
    put_status("maxLineGap", maxLineGap, 150);
  }
}

int main(int argc, char **argv) {
  cv::Mat canny;
  cv::Mat blank = cv::Mat::zeros(200, 400, CV_8U);
  const char *winName = "hough lines";
  const char *msgName = "message";
  cv::namedWindow(msgName, cv::WINDOW_AUTOSIZE);
  cv::namedWindow(winName, cv::WINDOW_AUTOSIZE);
  cv::moveWindow(msgName, 200, 300);
  cv::moveWindow(winName, 620, 300);

  cv::CommandLineParser parser(
      argc, argv,
      "{help| |This program will run a canny and a houghline detector}"
      "{image|| a grayscale image}"
      "{hough_type|2|1=houghline 2=houghlineP}");
  if (parser.has("help")) {
    parser.printMessage();
  }
  cv::Mat input_image =
      cv::imread(parser.get<cv::String>("image"), cv::IMREAD_GRAYSCALE);
  hough_type = parser.get<int>("hough_type");
  if (input_image.empty()) {
    std::cout << "Failed to load image: " << argv[1] << '\n';
    return 1;
  }
  if (!parser.check()) {
    parser.printErrors();
  }
  cv::Canny(input_image, canny, 50, 200, 3);

  if (hough_type == 1) {
    std::cout << "Increase decrease rho:        q, w\n"
                 "Increase decrease theta:      e, r\n"
                 "Increase decrease threshold:  t, y\n\n";
    while (true) {
      cv::cvtColor(blank, color_image, cv::COLOR_GRAY2BGR);
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
      auto key = static_cast<char>(cv::waitKey(0));
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
        std::cout << std::string("current rho: \t\t") + std::to_string(rho) +
                         "\n" + "current theta: \t\t" + std::to_string(theta) +
                         "\n"
                         "current threshold: \t" +
                         std::to_string(threshold) + "\n";
      }
      cv::imshow(msgName, color_image);
    }
  } else {

    std::cout << "Increase decrease rho:        q, w\n"
                 "Increase decrease theta:      e, r\n"
                 "Increase decrease threshold:  t, y\n"
                 "Increase decrease minLineLen: a, s\n"
                 "Increase decrease maxLineGap: d, f\n\n";
    while (true) {
      cv::cvtColor(blank, color_image, cv::COLOR_GRAY2BGR);
      cv::cvtColor(input_image, output_image, cv::COLOR_GRAY2BGR);
      std::vector<cv::Vec4i> lines;
      cv::HoughLinesP(canny, lines, rho, theta, threshold, minLineLen,
                      maxLineGap);
      for (const auto &line : lines) {
        cv::line(output_image, cv::Point2i(line[0], line[1]),
                 cv::Point2i(line[2], line[3]), cv::Scalar(0, 0, 255), 2,
                 cv::LINE_AA);
      }
      cv::imshow(winName, output_image);
      auto key = static_cast<char>(cv::waitKey(0));
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
      if (key == 'a') {

        increment(minLineLen, 3.0, "minLineLen");
      }
      if (key == 's') {
        if (minLineLen > 3 + eps) {
          increment(minLineLen, -3.0, "minLineLen");
        }
      }
      if (key == 'd') {
        increment(maxLineGap, 3.0, "maxLineGap");
      }
      if (key == 'f') {
        if (maxLineGap > 3 + eps) {
          increment(maxLineGap, -3.0, "maxLineGap");
        }
      }

      if (static_cast<int>(key) == 27) {
        break;
      }
      if (key == 'i') {
        std::cout << std::string("current rho: \t\t") + std::to_string(rho) +
                         "\n" + "current theta: \t\t" + std::to_string(theta) +
                         "\n"
                         "current threshold: \t" +
                         std::to_string(threshold) +
                         "\n"
                         "current minLineLen: " +
                         std::to_string(minLineLen) +
                         "\n"
                         "current maxLineGap: " +
                         std::to_string(maxLineGap) + "\n\n";
      }
      cv::imshow(msgName, color_image);
    }
  }
  return 0;
}