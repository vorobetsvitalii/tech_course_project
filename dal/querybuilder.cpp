#include "querybuilder.h"

void QueryBuilder::InsertQueryBuild(const QString &insert_query)
{
    DBExecutor dbexecutorInstanse;

    dbexecutorInstanse.Insert(insert_query);
}

void QueryBuilder::InsertQueryBuild(const QString table_name, const QList<QString> &columns_name, const QList<QString> &data_table)
{
    DBExecutor dbexecutorInstanse;
    QString insertQuery = "INSERT INTO " + table_name + " (";

    AppendColumnsName(&insertQuery, columns_name);

    insertQuery += ")\nVALUES";

    int count = 1;

    for(uint8_t i = 0; i < data_table.size(); i++)
    {
        if(count == 1)
        {
            insertQuery += "\n('" + data_table[i];
        }
        else
        {
            if(count == columns_name.size())
            {
                insertQuery += "', '" + data_table[i] + "')";
                count = 0;
            }
            else { insertQuery += "', '" + data_table[i]; }
        }
        count++;
    }

    dbexecutorInstanse.Insert(insertQuery);
}

QString QueryBuilder::SelectQueryBuild(const QString &select_query)
{
    DBExecutor dbexecutorInstanse;

    return dbexecutorInstanse.Select(select_query);;
}

QString QueryBuilder::SelectQueryBuild(const QString table_name, const QList<QString> &columns_name)
{
    DBExecutor dbexecutorInstanse;
    QString selectQuery = "SELECT ";

    AppendSelectQueryArgs(&selectQuery, table_name, columns_name);

    return dbexecutorInstanse.Select(selectQuery);
}

QString QueryBuilder::SelectQueryBuild(const QString table_name, const QList<QString> &columns_name, const str_qpaired_qlist &where_cond)
{
    DBExecutor dbexecutorInstanse;
    QString selectQuery = "SELECT ";

    AppendSelectQueryArgs(&selectQuery, table_name, columns_name);

    AppendWhereCond(&selectQuery, where_cond);

    return dbexecutorInstanse.Select(selectQuery);
}

void QueryBuilder::DeleteQueryBuild(const QString &delete_query)
{
    DBExecutor dbexecutorInstanse;

    dbexecutorInstanse.Delete(delete_query);
}

void QueryBuilder::DeleteQueryBuild(const QString table_name, const str_qpaired_qlist &where_cond)
{
    DBExecutor dbexecutorInstanse;
    QString deleteQuery = "DELETE FROM ";

    deleteQuery += table_name;

    AppendWhereCond(&deleteQuery, where_cond);

    dbexecutorInstanse.Delete(deleteQuery);
}

void QueryBuilder::UpdateQueryBuild(const QString &update_query)
{
    DBExecutor dbexecutorInstanse;

    dbexecutorInstanse.Update(update_query);
}

void QueryBuilder::UpdateQueryBuild(const QString table_name, const str_qpaired_qlist &data_table)
{
    DBExecutor dbexecutorInstanse;
    QString updateQuery = "UPDATE " + table_name + " SET ";

    AppendUpdateQueryArgs(&updateQuery, data_table);

    dbexecutorInstanse.Update(updateQuery);
}

void QueryBuilder::UpdateQueryBuild(const QString table_name, const str_qpaired_qlist &data_table, const str_qpaired_qlist &where_cond)
{
    DBExecutor dbexecutorInstanse;
    QString updateQuery = "UPDATE " + table_name + " SET ";

    AppendUpdateQueryArgs(&updateQuery, data_table);

    AppendWhereCond(&updateQuery, where_cond);

    dbexecutorInstanse.Update(updateQuery);
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

const void QueryBuilder::AppendUpdateQueryArgs(QString *updateQuery, const str_qpaired_qlist &data_table)
{
    for(uint8_t i = 0; i < data_table.size(); i++)
    {
        if(i == 0)
        {
            *updateQuery += data_table[i].first + "='" + data_table[i].second + "'";
        }
        else { *updateQuery += ", " + data_table[i].first + "='" + data_table[i].second + "'"; }
    }
}

const void QueryBuilder::AppendWhereCond(QString *anyQuery, const str_qpaired_qlist &where_cond)
{
    for(uint8_t i = 0; i < where_cond.size(); i++)
    {
        if(i != 0)
        {
            *anyQuery += " AND " + where_cond[i].first + "='" + where_cond[i].second + "'";
        }
        else { *anyQuery += " WHERE " + where_cond[i].first + "='" + where_cond[i].second + "'"; }
    }
}
