    #include "rack.hpp"
    
    struct SafeMenuItem : rack::ui::MenuItem {
      private:
        static constexpr const char* defaultConfirmText = "Are you sure?";

        std::string confirmText;
        std::string confirmButtonText;
        std::function<void ()> action;
        bool alwaysConsume;

      public:
        SafeMenuItem (
            std::string text,
            std::string confirmButtonText,
            std::function<void ()> action,
            bool alwaysConsume = false,
            std::string confirmText = defaultConfirmText
        ) : confirmText (confirmText),
            confirmButtonText (confirmButtonText),
            action (action),
            alwaysConsume (alwaysConsume) { this->text = text; }

        SafeMenuItem (
            std::string text,
            std::function<void ()> action,
            bool alwaysConsume = false,
            std::string confirmText = defaultConfirmText
        ) : SafeMenuItem (text, text, action, alwaysConsume, confirmText) { }

        void onAction (const rack::event::Action& e) override;
    };