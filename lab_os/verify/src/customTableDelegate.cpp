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
            // Число атомов углерода в углеводородном газе (x), ед.
            case 0:
                low = 0.0; hi = 4.0;
                isOkRange = (value >= low && value <= hi);
                break;
            // Число атомов водорода в углеводородном газе, ед.",
            case 1:
                low = 0.0; hi = 50.0;
                isOkRange = (value >= low && value <= hi);
                break;
            // Теплота сгорания углеводородного газа, МДж/м^3",
            case 2:
                low = 1.0; hi = 20000.0;
                isOkRange = (value >= low && value <= hi);
                break;
            // Верхний концентрационный предел воспламенения, %
            case 3:
                low = 0.01; hi = 99.0;
                isOkRange = (value >= low && value <= hi);
                break;
            // Плотность углеводородного газа при нормальных условиях, кг/м^3"
            case 4:
                low = 0.01; hi = 10.0;
                isOkRange = (value >= low && value <= hi);
                break;
            // Нормальная скорость распространения пламени, м/c",
            case 5:
                low = 0.001; hi = 10.0;
                isOkRange = (value >= low && value <= hi);
                break;
            // Масса углеводородного газа, образовавшего огневой шар, т",
            case 6:
                low = 1.0; hi = 50000;
                isOkRange = (value >= low && value <= hi);
                break;
            // Расстояние от зоны горения до приёмника ИК излучения, м"
            case 7:
                low = 1.0; hi = 10000;
                isOkRange = (value >= low && value <= hi);
                break;
            // Время действия излучения на сетчатку глаза человека, с"
            case 8:
                low = 0.00001; hi = 100000;
                isOkRange = (value >= low && value <= hi);
                break;
            default:
                // Если нет ограничений
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
        painter->drawText(option.rect, Qt::AlignCenter | Qt::AlignVCenter, text);
    }
    else {
        QStyledItemDelegate::paint(painter, option, index);
    }
}

// End customTableDelegate.cpp
