#include <vector>
using namespace std;

class IDBConnection {
};

class IDBCommand {
};

class IDataReader {
};

class IDBFactory {
public:
    virtual IDBConnection* CreateDBConnection() = 0;
    virtual IDBCommand* CreateDBCommand() = 0;
    virtual IDataReader* CreateDataReader() = 0;
};

class SqlConnection : public IDBConnection {
};

class SqlCommand : public IDBCommand {
};

class SqlDataReader : public IDataReader {
};

class SqlDBFactory : public IDBFactory {
public:
    virtual IDBConnection* CreateDBConnection() = 0;
    virtual IDBCommand* CreateDBCommand() = 0;
    virtual IDataReader* CreateDataReader() = 0;
};

// 支持Oracle
class OracleConnection : public IDBConnection {
};

class OracleCommand : public IDBCommand {
};

class OracleDataReader : public IDataReader {
};

class OracleDBFactory : public IDBFactory {
public:
    virtual IDBConnection* CreateDBConnection() = 0;
    virtual IDBCommand* CreateDBCommand() = 0;
    virtual IDataReader* CreateDataReader() = 0;
};

class EmployeeDAO {
    IDBFactory* dbFactory;

public:
    vector<EmployeeDAO> GetEmployees()
    {
        IDBConnection* connection = dbFactory->CreateDBConnection();
        // connection->ConnectionString("...");

        IDBCommand* command = dbFactory->CreateDBCommand();
        // command->CommandText("...");
        // command->SetConnection(connection); //关联性

        // IDBDataReader* reader = command->ExecuteReader(); //关联性
    }
};