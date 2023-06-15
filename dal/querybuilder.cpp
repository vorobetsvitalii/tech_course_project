#include "querybuilder.h"

QString QueryBuilder::InsertQueryBuild(const QString table_name, const QList<QString> &columns_name, const QList<QString> &data_table, const double rows_count)
{
    if(columns_name.size() != data_table.size() / rows_count) { std::cout << "Invalid query! "; throw "Invalid query!"; }

    QString insertQuery = "INSERT INTO " + table_name + " (";

    AppendColumnsName(&insertQuery, columns_name);

    insertQuery += ")\nVALUES";

    int count = 1;

    for(uint8_t i = 0; i < data_table.size(); i++)
    {
        if(count == 1)
        {
            insertQuery += "\n(" + data_table[i];
        }
        else
        {
            if(count == columns_name.size())
            {
                insertQuery += ", " + data_table[i] + ")";
                count = 0;
            }
            else { insertQuery += ", " + data_table[i]; }
        }
        count++;
    }

    return (insertQuery + ";");
}

QString QueryBuilder::SelectQueryBuild(const QString table_name, const QList<QString> &columns_name)
{
    QString selectQuery = "SELECT ";

    AppendSelectQueryArgs(&selectQuery, table_name, columns_name);

    return (selectQuery + ";");
}

QString QueryBuilder::SelectQueryBuild(const QString table_name, const QList<QString> &columns_name, const str_qpaired_qlist &where_cond)
{
    QString selectQuery = "SELECT ";

    AppendSelectQueryArgs(&selectQuery, table_name, columns_name);

    AppendWhereCond(&selectQuery, where_cond);

    return (selectQuery + ";");
}

QString QueryBuilder::DeleteQueryBuild(const QString table_name, const str_qpaired_qlist &where_cond)
{
    QString deleteQuery = "DELETE FROM ";

    deleteQuery += table_name;

    AppendWhereCond(&deleteQuery, where_cond);

    return (deleteQuery + ";");
}

QString QueryBuilder::UpdateQueryBuild(const QString table_name, const str_qpaired_qlist &data_table, const str_qpaired_qlist &where_cond)
{
    QString updateQuery = "UPDATE " + table_name + " SET ";

    for(uint8_t i = 0; i < data_table.size(); i++)
    {
        if(i == 0)
        {
            updateQuery += data_table[i].first + "=" + data_table[i].second;
        }
        else { updateQuery += ", " + data_table[i].first + "=" + data_table[i].second; }
    }

    AppendWhereCond(&updateQuery, where_cond);

    return (updateQuery + ";");
}

const void QueryBuilder::AppendColumnsName(QString *anyQuery, const QList<QString> &columns_name)
{
    for(uint8_t i = 0; i < columns_name.size(); i++)
    {
        if(i == 0)
        {
            *anyQuery += columns_name[i];
        }
        else { *anyQuery += ", " + columns_name[i]; }
    }
}

const void QueryBuilder::AppendSelectQueryArgs(QString* selectQuery, const QString &table_name, const QList<QString> &columns_name)
{
    AppendColumnsName(selectQuery, columns_name);

    *selectQuery += " FROM " + table_name;
}

const void QueryBuilder::AppendWhereCond(QString *anyQuery, const str_qpaired_qlist &where_cond)
{
    for(uint8_t i = 0; i < where_cond.size(); i++)
    {
        if(i != 0)
        {
            *anyQuery += " AND " + where_cond[i].first + "=" + where_cond[i].second;
        }
        else { *anyQuery += " WHERE " + where_cond[i].first + "=" + where_cond[i].second; }
    }
}
