// Copyright 2018 Aubin REBILLAT
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef BROWSER_DELEGATE_H_
# define BROWSER_DELEGATE_H_

#include <eglcontent/browser_delegate.h>

#include "dbus_interface.h"

class RpiBrowserDelegate : public EGLContent::BrowserDelegate {

  public:

    RpiBrowserDelegate();
    ~RpiBrowserDelegate();

    void BrowserCreated(EGLContent::BrowserDelegate::Controller* controller) override;
    void LoadingStateChanged(bool loading) override;
    void LoadProgressed(double progress) override;
    void TargetURLChanged(std::string& url) override;

  private:

    DbusInterface dbus_interface_;

};

#endif /* !BROWSER_DELEGATE.H */
