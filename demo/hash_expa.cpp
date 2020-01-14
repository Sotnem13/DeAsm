//
// Created by sotnem on 13.01.20.
//

//struct Has
//using Hash = uint64_t;
//
//struct Processor {
//
//    int i = 0;
//
//    std::string info() {
//        return std::to_string(i) + " " + semiInfo();
//    }
//
//    std::string semiInfo() {
//        return "wola diAsm";
//    }
//
//    uint64_t hash() {
//        return std::hash<std::string>()(info());
//    }
//
//    uint64_t semiHash() {
//        return std::hash<std::string>()(semiInfo());
//    }
//
//};
//
//struct Profile {
//
//    int i = 0;
//    std::string semiInfo;
//
//    bool hasFullHash() {
//        return i!=0;
//    }
//
//    std::string info() {
//        return std::to_string(i) + " " + semiInfo();
//    }
//
//    uint64_t hash() {
//        return std::hash<std::string>()(info());
//    }
//
//    uint64_t semiHash() {
//        return std::hash<std::string>()(semiInfo());
//    }
//
//};
//
//struct Provider {
//
//
//    Processor* get(Profile& p) {
//        auto hash = p.hash();
//        auto semiHash = p.semiHash();
//
//        if (p.hasFullHash()) {
//            auto it = std::find_if(objs.begin(), objs.end(), [=](auto p) {
//                return p.hash() == hash;
//            });
//            if (it != end(objs)) {
//                return &(*it);
//            }
//        } else {
//            auto it = std::find_if(objs.begin(), objs.end(), [=](auto p) {
//                return p.semiHash() == semiHash;
//            });
//            if (it != end(objs)) {
//                return &(*it);
//            }
//        }
//
//
//
//    }
//
//    std::vector<Processor> objs;
//
//};
//
//
//
//
//int main() {
//
//    Provider
//
//}
