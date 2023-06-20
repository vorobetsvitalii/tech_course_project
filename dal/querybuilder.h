#ifndef QUERYBUILDER_H
#define QUERYBUILDER_H

#include <iostream>
#include <QList>
#include <QMap>
#include "dbexecutor.h"

using str_qpaired_qlist = QList<QPair<QString, QString>>;

class QueryBuilder
{
public:
    QueryBuilder() = delete;

    static void InsertQueryBuild(const QString &insert_query);
    static void InsertQueryBuild(const QString table_name, const QList<QString> &columns_name, const QList<QString> &data_table);
    static QString SelectQueryBuild(const QString &select_query);
    static QString SelectQueryBuild(const QString table_name, const QList<QString> &columns_name);
    static QString SelectQueryBuild(const QString table_name, const QList<QString> &columns_name, const str_qpaired_qlist &where_cond);
    static void DeleteQueryBuild(const QString &delete_query);
    static void DeleteQueryBuild(const QString table_name, const str_qpaired_qlist &where_cond);
    static void UpdateQueryBuild(const QString &update_query);
    static void UpdateQueryBuild(const QString table_name, const str_qpaired_qlist &data_table);
    static void UpdateQueryBuild(const QString table_name, const str_qpaired_qlist &data_table, const str_qpaired_qlist &where_cond);

private:
    static const void AppendColumnsName(QString* anyQuery, const QList<QString> &columns_name);
    static const void AppendSelectQueryArgs(QString* selectQuery, const QString &table_name, const QList<QString> &columns_name);
    static const void AppendUpdateQueryArgs(QString* updateQuery, const str_qpaired_qlist &data_table);
    static const void AppendWhereCond(QString* anyQuery, const str_qpaired_qlist &where_cond);
};

#endif // QUERYBUILDER_H
