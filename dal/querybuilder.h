#ifndef QUERYBUILDER_H
#define QUERYBUILDER_H

#include <iostream>
#include <QList>
#include <QMap>

using str_qpaired_qlist = QList<QPair<QString, QString>>;

class QueryBuilder
{
public:
    QueryBuilder() = delete;
    static QString InsertQueryBuild(const QString table_name, const QList<QString> &columns_name, const QList<QString> &data_table, const double rows_count);
    static QString SelectQueryBuild(const QString table_name, const QList<QString> &columns_name);
    static QString SelectQueryBuild(const QString table_name, const QList<QString> &columns_name, const str_qpaired_qlist &where_cond);
    static QString DeleteQueryBuild(const QString table_name, const str_qpaired_qlist &where_cond);
    static QString UpdateQueryBuild(const QString table_name, const str_qpaired_qlist &data_table, const str_qpaired_qlist &where_cond);

private:
    static const void AppendColumnsName(QString* anyQuery, const QList<QString> &columns_name);
    static const void AppendSelectQueryArgs(QString* selectQuery, const QString &table_name, const QList<QString> &columns_name);
    static const void AppendWhereCond(QString* anyQuery, const str_qpaired_qlist &where_cond);
};

#endif // QUERYBUILDER_H
