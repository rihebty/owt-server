/*
 * Copyright 2014 Intel Corporation All Rights Reserved.
 *
 * The source code contained or described herein and all documents related to the
 * source code ("Material") are owned by Intel Corporation or its suppliers or
 * licensors. Title to the Material remains with Intel Corporation or its suppliers
 * and licensors. The Material contains trade secrets and proprietary and
 * confidential information of Intel or its suppliers and licensors. The Material
 * is protected by worldwide copyright and trade secret laws and treaty provisions.
 * No part of the Material may be used, copied, reproduced, modified, published,
 * uploaded, posted, transmitted, distributed, or disclosed in any way without
 * Intel's prior express written permission.
 *
 * No license under any patent, copyright, trade secret or other intellectual
 * property right is granted to or conferred upon you by disclosure or delivery of
 * the Materials, either expressly, by implication, inducement, estoppel or
 * otherwise. Any license under such intellectual property rights must be express
 * and approved by Intel in writing.
 */

#ifndef VideoLayoutProcessor_h
#define VideoLayoutProcessor_h

#include "VideoLayout.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/shared_ptr.hpp>
#include <EventRegistry.h>
#include <list>
#include <logger.h>
#include <map>
#include <vector>

namespace mcu {

class VideoLayoutProcessor {
    DECLARE_LOGGER();

public:
    VideoLayoutProcessor(boost::property_tree::ptree& layoutConfig);
    virtual ~VideoLayoutProcessor();

    void registerConsumer(boost::shared_ptr<LayoutConsumer>);
    void deregisterConsumer(boost::shared_ptr<LayoutConsumer>);

    bool getRootSize(woogeen_base::VideoSize& rootSize);

    bool getBgColor(woogeen_base::YUVColor& bgColor);

    void addInput(int input, bool toFront = false);
    void addInput(int input, std::string& specifiedRegionID);
    void removeInput(int input);
    void promoteInput(int input, size_t magnitude);
    void promoteInputs(std::vector<int>& inputs);
    bool specifyInputRegion(int input, const std::string& regionID);
    std::string getInputRegion(int input);
    // Get detail region for layout
    Region getRegionDetail(int input);
    void setEventRegistry(EventRegistry* handle) { m_eventHandle = handle; }

private:
    void updateInputPositions();
    void chooseRegions();

private:
    std::list<boost::shared_ptr<LayoutConsumer>> m_consumers;
    woogeen_base::VideoSize m_rootSize;
    woogeen_base::YUVColor m_bgColor;
    std::vector<int> m_inputPositions;
    std::vector<Region>* m_currentRegions;
    std::map<size_t /*MaxInputCount*/, std::vector<Region>> m_templates;
    EventRegistry* m_eventHandle;
};
}
#endif