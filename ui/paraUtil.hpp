#ifndef PARAUTIL_HPP
#define PARAUTIL_HPP

#include "../Scheme/Para.hpp"
#include <QComboBox>

namespace util {
    /**
     * @brief buildComboBox
     *          build comboBox with para's orParas
     *          connect with selectPara
     *          set default one's selectedType
     * @param comboBox
     * @param para
     */
    void buildComboBox(QComboBox*& comboBox, scheme::Para& para);
    /**
     * @brief selectPara
     *          if not multi, set only selected para to SINGLE, else to INCOMPLETE
     *          then set dest's selectedType
     * @param dest
     * @param selected
     * @param isMultiSelect
     */
    void selectPara(scheme::Para::Para* dest, scheme::Para* selected, bool isMultiSelect = false);

    bool isSelected(scheme::Para::SelectedType type);
    bool isSelected(const scheme::Para& para);
    bool isMultiSelected(const scheme::Para& para);

    bool isLeaf(const scheme::Para& para);
    bool isCheckBoxGroup(const scheme::Para& para);
    bool hasComboBox(const scheme::Para& para);
}

#endif // PARAUTIL_HPP
