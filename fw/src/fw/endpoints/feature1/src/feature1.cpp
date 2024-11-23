#include "feature1.h"

class F123 : public BaseEndpoint
{
public:
    F123()
    {
        feature1ServiceInjections = new Feature1ServiceInjections();
        feature1ServiceInjections->feature1ServiceData_ = new Feature1ServiceData();
        feature1ServiceInjections->utils_ = new Utils();
        f1 = new Feature1Service(feature1ServiceInjections);
        for (auto &route : getRoutes()){
            addRoute(route);
        }
    }
    ~F123()
    {
        std::cout << "F123 destructor" << std::endl;
    }
    std::vector<Route> getRoutes()
    {
        std::vector<Route> routes;
        return routes;
    }

    void getPersons(RouteContext routeContext)
    {
        logger.info("F123::getPersons Enter");
        routeContext.res->body = objectToJson(f1->getPersons(routeContext.req->query_params));
        logger.info("F123::getPersons Exit");
    }
    void getPerson(RouteContext routeContext)
    {
        logger.info("F123::getPerson Enter");
        Person *p = f1->getPerson(routeContext.path_params["id"]);
        if (p == nullptr)
        {
            routeContext.res->status_code = 404;
            routeContext.res->body = "Person not found";
        }
        else
        {
            routeContext.res->body = objectToJson(*p);
        }
        logger.info("F123::getPerson Exit");
    }
    void addPerson(RouteContext routeContext)
    {
        logger.info("F123::addPerson Enter");
        Person p;
        try
        {
            p = jsonToObject<Person>(routeContext.req->body);
            routeContext.res->body = objectToJson(f1->addPerson(p));
        }
        catch (const std::exception &e)
        {
            routeContext.res->status_code = 400;
            routeContext.res->body = e.what();
        }
        logger.info("F123::addPerson Exit");
    }

private:
    Logger logger;
    Feature1Service *f1;
    Feature1ServiceInjections *feature1ServiceInjections;
};

Feature1::Feature1()
{
    Route route;
    route.path = "/ronak";
    route.method = RouteMethod::GET;
    route.handler = [this](RouteContext routeContext)
    {
        logger.info("Feature1::ronak Enter");
        routeContext.res->body = "Feature1 GET request";
        logger.info("Feature1::ronak Exit");
    };
    addRoute(route);
    addSubRouter("f123", std::make_shared<F123>());
}