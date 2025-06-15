// Begin customTableDelegate.cpp

#include "customTableDelegate.h"

CustomTableDelegate::CustomTableDelegate(QObject* parent) :
                                                    QStyledItemDelegate(parent){
}

QWidget* CustomTableDelegate::createEditor(QWidget* parent,
                                           const QStyleOptionViewItem& option,
                                           const QModelIndex& index) const {
    QLineEdit* editor = new QLineEdit(parent);
    editor->setAlignment(Qt::AlignCenter);
    return editor;
}

void CustomTableDelegate::setEditorData(QWidget* editor,
                                              const QModelIndex& index) const {
    QString value = index.model()->data(index, Qt::EditRole).toString();
    QLineEdit* line = static_cast<QLineEdit*>(editor);
    line->setText(value.replace(".", ","));
}

void CustomTableDelegate::setModelData(QWidget* editor,
                                       QAbstractItemModel* model,
                                       const QModelIndex& index) const{
    QLineEdit* lineEdit = static_cast<QLineEdit*>(editor);
    QString text = lineEdit->text().replace(",", ".");
    bool ok;
    double value = text.toDouble(&ok);

    if (ok) {
        bool isOkRange = false;
        double low, hi;
        switch (index.row()) {
            // 1. Диаметр цилиндрического резервуара со сжатым газом, м.
            case 0:
                low = 1.0E-5; hi = 1.0E8;
                isOkRange = (value >= low && value <= hi);
                break;
            // 2. Длина цилиндрического резервуара со сжатым газом, м.
            case 1:
                low = 1.0E-7; hi = 1.0E7;
                isOkRange = (value >= low && value <= hi);
                break;
            // 3. Показатель адиабаты сжатого газа в резервуаре.
            case 2:
                low = 1.0E-3; hi = 1.0E4;
                isOkRange = (value >= low && value <= hi);
                break;
            // 4. Избыточное давление сжатого газа в резервуаре при взрыве, кПа
            case 3:
                low = 1.0E-3; hi = 9.0E5;
                isOkRange = (value >= low && value <= hi);
                break;
            // 5. Плотность газа при нормальных условиях, кг/м^3.
            case 4:
                low = 1.0E-4; hi = 1.0E3;
                isOkRange = (value >= low && value <= hi);
                break;
            // 6. Температура воздуха, град. Цельсия.
            case 5:
                low = 1.0E-2; hi = 1.0E6;
                isOkRange = (value >= low && value <= hi);
                break;
            // 7. Коэффициент перехода
            case 6:
                low = 1.0E-2; hi = 1.0;
                isOkRange = (value >= low && value <= hi);
                break;
            // 8. Расстояние от центра взрывной сист. до приёмника уд. волны, м.
            case 7:
                low = 1.0E-3; hi = 9.0E5;
                isOkRange = (value >= low && value <= hi);
                break;
            default:
                // Иные ячейки без ограничений
                isOkRange = true;
        }

        if (isOkRange) {
            model->setData(index, value, Qt::EditRole);
        }
        else {
            QString msg;
            msg = "Введите вещественное число в диапазоне от %1 до %2";
            msg = msg.arg(low).arg(hi);
            QMessageBox::warning(editor, "Ошибка", msg);
        }
    }
    else {
        QMessageBox::warning(editor, "Ошибка", "Ожидается ввод числа!");
    }
}

void CustomTableDelegate::paint(QPainter* painter,
                                    const QStyleOptionViewItem& option,
                                    const QModelIndex &index) const {
    // Draw double number with "comma"
    if (index.data().canConvert<double>()) {
        double nVal = index.data().toDouble();

        QString text = QString::number(nVal).replace(".", ",");
        painter->drawText(option.rect, Qt::AlignCenter | Qt::AlignVCenter,text);
    }
    else {
        QStyledItemDelegate::paint(painter, option, index);
    }
}

// End customTableDelegate.cpp
