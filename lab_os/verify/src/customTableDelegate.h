// Begin customTableDelegate.h

#ifndef CUSTOMTABLEDELEGATE_H
#define CUSTOMTABLEDELEGATE_H 1

#include <QStyledItemDelegate>
#include <QMessageBox>
#include <QPainter>
#include <QLineEdit>
#include <QToolTip>
#include <QTimer>

class CustomTableDelegate : public QStyledItemDelegate
{
    Q_OBJECT
    public:
        explicit CustomTableDelegate(QObject* parent = 0);

    protected:
        QWidget* createEditor(QWidget* parent,
                              const QStyleOptionViewItem& option,
                              const QModelIndex& index) const;
        void setEditorData(QWidget* editor,
                              const QModelIndex& index) const;
        void setModelData(QWidget* editor,
                              QAbstractItemModel* model,
                              const QModelIndex& index) const;
        void paint(QPainter* painter,
                              const QStyleOptionViewItem& option,
                              const QModelIndex &index) const override;
};
#endif
// End customTableDelegate.h
