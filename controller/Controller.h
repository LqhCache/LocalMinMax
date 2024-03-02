/*
* @Author: Qianhua Liu
* @Date: 2024-01-06
* @Description: 
* @Note: Copyright (c) 2024, Qianhua Liu Inc., All rights reserved
*/
#ifndef LOCALMINMAX_CONTROLLER_CONTROLLER_H
#define LOCALMINMAX_CONTROLLER_CONTROLLER_H

#include <vector>
#include <memory>

#include "defectresolver/DefectResolver.h"
#include "measurement/MeasurePath.h"
#include "measurement/MpMeasurer.h"
#include "measurement/MeasureParam.h"

namespace localminmax::controller {
using MeasurePath = measurement::MeasurePath;
using MpMeasurer = measurement::MpMeasurer;
using MeasureParam = measurement::MeasureParam;
using DefectResolver = defectresolver::DefectResolver;

class Controller {
public:
    Controller() = default;
    Controller(const std::string& file_path);
    ~Controller() = default;
    bool run();
private:
    bool runMeasurement(std::string& error_msg);
    bool runResolver(std::string& error_msg);
    bool parseInputFile(std::string& error_msg);
    bool createMpMeasurer(std::string& error_msg);
    bool createDefectResolver(std::string& error_msg);

    std::string m_file_path;
    MeasureParam m_measure_param;
    std::shared_ptr<MeasurePath> m_measure_path1 = nullptr;
    std::shared_ptr<MeasurePath> m_measure_path2 = nullptr;
    std::shared_ptr<MpMeasurer> m_mp_measurer = nullptr;
    std::shared_ptr<DefectResolver> m_defect_resolver = nullptr;
};

} // localminmax::controller

#endif //LOCALMINMAX_CONTROLLER_CONTROLLER_H