/*
 *
 *    Copyright (c) 2021 Project CHIP Authors
 *    All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#pragma once

#include <app-common/zap-generated/cluster-objects.h>

#include <app/util/af.h>
#include <list>

namespace chip {
namespace app {
namespace Clusters {
namespace ApplicationLauncher {

using namespace chip::app::Clusters;
using namespace chip::app::Clusters::ApplicationLauncher::Structs;

/** @brief
 *    Defines methods for implementing application-specific logic for the Application Launcher Cluster.
 */
class Delegate
{
public:
    Delegate() : Delegate(false){};
    Delegate(bool featureMapContentPlatform) { mFeatureMapContentPlatform = featureMapContentPlatform; };

    inline bool HasFeature(ApplicationLauncherFeature feature)
    {
        if (feature == ApplicationLauncherFeature::kApplicationPlatform)
        {
            return mFeatureMapContentPlatform;
        }
        return false;
    }

    // this attribute should only be enabled for app platform instance (endpoint 1)
    Structs::ApplicationEP::Type HandleGetCurrentApp();

    // TODO: refactor this method signature to address memory issue (see PR 13398)
    virtual std::list<uint16_t> HandleGetCatalogList() = 0;

    virtual Commands::LauncherResponse::Type HandleLaunchApp(const CharSpan & data,
                                                             const ApplicationLauncherApplication::Type & application) = 0;
    virtual Commands::LauncherResponse::Type HandleStopApp(const ApplicationLauncherApplication::Type & application)   = 0;
    virtual Commands::LauncherResponse::Type HandleHideApp(const ApplicationLauncherApplication::Type & application)   = 0;

    virtual ~Delegate() = default;

protected:
    bool mFeatureMapContentPlatform = false;
};

} // namespace ApplicationLauncher
} // namespace Clusters
} // namespace app
} // namespace chip
