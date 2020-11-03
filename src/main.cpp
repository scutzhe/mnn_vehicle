#include "Vehicle.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

int main(int argc, char **argv) {
    if (argc <= 2) {
        fprintf(stderr, "Usage: %s <mnn .mnn> [image files...]\n", argv[0]);
        return 1;
    }

    string mnn_path = argv[1];
    Vehicle vehicle(mnn_path, 384, 192, 4, 0.65); // config model input

    for (int i = 2; i < argc; i++) {
        string image_file = argv[i];
        cout << "Processing " << image_file << endl;

        cv::Mat frame = cv::imread(image_file);
        auto start = chrono::steady_clock::now();
        vector<VehicleInfo> vehicle_info;
        vehicle.detect(frame, vehicle_info);

        for (auto vehicle : vehicle_info) {
            cv::Point pt1(vehicle.x1, vehicle.y1);
            cv::Point pt2(vehicle.x2, vehicle.y2);
            cv::rectangle(frame, pt1, pt2, cv::Scalar(0, 255, 0), 2);
        }

        auto end = chrono::steady_clock::now();
        chrono::duration<double> elapsed = end - start;
        cout << "all time: " << elapsed.count() << " s" << endl;
        cv::imshow("vehicle_detection", frame);
        cv::waitKey();
        string result_name = "result" + to_string(i) + ".jpg";
        cv::imwrite(result_name, frame);
    }
    return 0;
}
