#pragma once
#include <vector>
#include <functional>
#include "ObjectBase.h"

namespace shooting {

    class ManagerBase {
    public:
        ManagerBase(const int screenWidth, const int screenHeight);
        virtual ~ManagerBase();

        virtual void Process();
        virtual void Render();

        std::vector<ObjectBase*>& GetManagedList() {
            return managedList;
        }

    protected:
        ObjectBase* GetInvalid() const;
        bool Spawn(int maxNumber,
                   std::function<ObjectBase*(int, int)> generator,
                   std::function<bool(ObjectBase*)> starter);

        std::vector<ObjectBase*> managedList;

        int screenWidth;
        int screenHeight;
    };
}
