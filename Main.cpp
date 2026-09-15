#include "MiniLogger.h"
#include "ConsoleSink.h"
#include "FileSink.h"

int main()
{
    Logger logger(LogLevel::DEBUG);

   logger.addSink(
        std::make_shared<ConsoleSink>()
    );

    logger.addSink(
        std::make_shared<FileSink>("app.log")
    );

    std::thread t1([&]()
        {
            logger.info("AAA");
        });

    std::thread t2([&]()
        {
            logger.info("BBB");
        });

    t1.join();
    t2.join();

    return 0;
}