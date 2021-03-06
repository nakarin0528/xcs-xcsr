#pragma once

#include "../XCS/match_set.h"

namespace XCSR
{

    template <typename T, typename Action, class Symbol, class Condition, class Classifier, class Constants, class ClassifierPtrSet, class Population>
    class MatchSet : public XCS::MatchSet<T, Action, Symbol, Condition, Classifier, Constants, ClassifierPtrSet, Population>
    {
    protected:
        using ClassifierPtr = std::shared_ptr<Classifier>;
        using ClassifierPtrSet::m_set;
        using ClassifierPtrSet::m_constants;
        using ClassifierPtrSet::m_availableActions;

        // GENERATE COVERING CLASSIFIER
        virtual ClassifierPtr generateCoveringClassifier(const std::vector<T> & situation, const std::unordered_set<Action> & unselectedActions, uint64_t timeStamp) const override
        {
            std::vector<Symbol> symbols;
            for (auto && symbol : situation)
            {
                symbols.emplace_back(symbol, XCS::Random::nextDouble(0.0, m_constants.maxSpread));
            }

            return std::make_shared<Classifier>(symbols, XCS::Random::chooseFrom(unselectedActions), timeStamp, m_constants);
        }

    public:
        // Constructor
        using XCS::MatchSet<T, Action, Symbol, Condition, Classifier, Constants, ClassifierPtrSet, Population>::MatchSet;

        // Destructor
        virtual ~MatchSet() = default;
    };

}