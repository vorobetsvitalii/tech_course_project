#include "dbmodel.h"
#include "../dal/querybuilder.h"


void DbModel::Insert(const QString &insert_query)
{
    QueryBuilder::InsertQueryBuild(insert_query);
}

QString DbModel::Select(const QString &select_query)
{
    return QueryBuilder::SelectQueryBuild(select_query);
}

void DbModel::Update(const QString &update_query)
{
    QueryBuilder::UpdateQueryBuild(update_query);
}

void DbModel::Delete(const QString &delete_query)
{
    QueryBuilder::DeleteQueryBuild(delete_query);
}
