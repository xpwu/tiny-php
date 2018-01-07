# tiny-php

tiny-php 是一个超级小的php服务器的工程代码结构，它不是一个框架。集成了事件机制，定时器逻辑。整个工程的集成需要使用[phpinte](https://github.com/xpwu/php-integrate).

## php
服务器代码目录，tiny文件夹是公共的常用库，用户的工程文件放到project文件夹中。

### <a name="Event"></a>事件(Event)
采用Event-Listener模式实现事件机制。 
 
1. Event分类。   
Event一共分两种，1）、定时器事件：TimerEvent或者继承自TimerEvent的事件；2）、普通事件：直接继承自Event的事件或者其他普通事件的事件。  
2. Listener注册。  
Listener注册到事件中心(EventCenter)有两种方式：1）、手动注册：使用Tiny\Event\EventCenter->addListener注册一个Listener，对应的可以使用removeListener反注册一个Listener；2）、自动注册：实现一个Tiny\Event\EventCenterAutoRegistrator的子类，在listener()方法中返回要注册的Listener。自动注册可以在运行时自动注册（在ProjectInit.init中添加`Tiny\Event\EventCenterAutoRegistrator::registerAllListener()`），也可以在集成时自动注册（在集成之前，运行`tiny/build/buildAutoEventData.sh`，再使用phpinte集成整个工程）。**注意：**定时器事件只能使用手动注册方式。   
3. Listener使用   
定义一个继承自Listener的子类，实现handler方法，即定义了一个Listener，一个Listener只能监听一个具体的Event，在Listener的构造函数中指定监听的具体Event。
4. 事件的使用。   
定义一个\Tiny\Event的子类即定义了一个新的事件，事件参数由各子事件决定，在调用父类的构造函数时，需要指定要参与事件区分的参数，如果没有参数参与事件区分，就传入`""`。 
  
```
class DemoEvent extends Event {
	function __construct(int $index, int $any) {
		parent::__construct($index);
 	}

	public function getIndex() {
		return $this->index_;
	}

	private $index_;
}  

```
对于以上Event，`new DemoEvent(3, 5)`与`new DemoEvent(4, 5)`是两个不同的事件，但是`new DemoEvnet(3, 5)`与`new DemoEvent(3, 10)`是两个相同的事件。Listener可以监听一个具体参数的事件，如果要监听此事件所有参数生成的事件，调用toAll()即可。

```
new Sub1Listener(new DemoEvent(7, 9));
```
生成了一个监听者，监听第一个参数为7的DemoEvent事件(第二个参数9未参与事件区分)。

```
$event = new DemoEvent(7, 9);
$evnet->toAll();
new Sub2Listener($event);
```
生成一个监听者，监听DemoEvent所有参数的事件。
当`new DemoEvent(7, 10)`事件产生时，SubListener 与 Sub2Listener 都将接收到事件，但当`new DemoEvent(5, 10)`事件产生时，只有Sub2Listener 能接收到事件。**注意：**没有参数的事件是一种特殊参数的事件，不等于All事件。   

```
$event1 = new SubEvent();
$event2 = new SubEvnet();
$event2->toAll();
```
`$event1`与`$event2`是不同的事件。   
   
5. 普通事件产生。   
普通事件一般由其他某个操作引起，事件生成后，使用`Tiny\Event\EventCenter::default()->postEvent($event)`把事件通知到所有的监听者。   
6. 定时器事件。    
php中没有实现定时源，php服务器的特点也不方便产生定时源，另外，定时事件仍可能需要走接入层的负载均衡，因此在tick目录下，实现了定时源，实现原理是定时请求指定的接口。接口中调用`Tiny\Event\EventCenter::default()->postTimerEvent()`把定时器事件通知到所有的监听者。tick的请求周期(单位为s)就是定时器的精度。   
TimerEvent中的context可以保留定时事件执行的上下文数据，传入的array必须保证json_encode成功。   
定时器事件的type参数可以把TimerEvent分类，方便timer数据库的管理，具体使用时建议使用子类的方式。

### <a name="Mongodb"></a>数据库(Mongodb)
tiny工程中使用Mongodb数据库，Event 与 TimerEvent均存储在Mongodb中，工程中可以继承`\Tiny\DB\MongoDB`或者`\Tiny\DB\MongodbDefault`生成一个新的数据库类，MongodbDefault的参数在配置中设定。对于需要建立除`_id`以外的索引时，可以`implements CreateIndexInterface`实现createIndex方法，这样可以方便使用代码自动统一建立索引。


### <a name="ProjectInit"></a>初始化(ProjectInit)
工程需要的初始化可以放在`ProjectInit::init()`中，在整个逻辑开始前，这里的代码会得到执行。比如监听器的运行时自动注册即是在此调用；如果工程要换其他日志系统也是在此调用响应的接口(参见[日志](#Logger)部分的说明)。

### <a name="Logger"></a>日志(Logger)
tiny在\Tiny\Logger定义了日志的基本接口，在\Tiny\Log4php中实现了log4php的适配，tiny工程默认使用Log4php作为日志的具体处理，使用Log4php需要在配置中正确的设置log4php包的位置。如果在具体的工程中要替换为其他Logger，可以在ProjectInit::init()中调用`Logger::setConcreteLogger($concreteLogger)`。

### <a name="Config"></a>配置(Config)
整个工程的配置在config.php文件中，使用php类常量的方式设定。此文件的加载可以在php.ini中配置为auto_prepend_file的参数，或者在[初始化](#ProjectInit)时`require_once`。在nginx环境中也可以使用如下指令修改`auto_prepend_file`的值。
单个值：

```
fastcgi_param PHP_VALUE "auto_prepend_file=/home/www/h1.php";
```
多个值(`\n`)分割：

```
fastcgi_param PHP_VALUE "auto_prepend_file=/home/www/h1.php \n auto_append_file=/home/www/h2.php";
```

### 接口(API)
接口必须继承自\Tiny\API 或者其子类，比如\Tiny\JsonApi(加入了json的编解码)，并实现run方法，子类的命名空间与类名无规定，但是整个完整类名也就是接口名。比如：NS\SubAPI 的类名的接口名就是/NS/SubAPI。接口对应于请求中URI去掉参数的部分，比如：127.0.0.1:10000/MyProject/GetInfo, 会自动调用 MyProject\GetInfo的run方法。   
\Tiny\API还有两个辅助方法：beforeRun afterRun，可在run执行的前后做一些处理，比如JsonApi 就用于编解码工作。   
API的请求参数用Request对象传递，其中data就是POST的数据；处理的结果使用Response传递，其中的data就是返回的数据。

### 错误日志   
错误日志的位置在php.ini的`error_log`项目配置，如果没有配置此项，默认为phar同级的error.log文件。

### project
实际工程的代码放置于此文件夹下，建立代码组织方式为：   

1. api：放所有的接口代码，也就是所有继承于 \Tiny\API的类均放置于此文件夹中，api中的代码可以调用module与db中的接口，api之间不能相互调用，api最主要的目的是验证用户的输入；
2. event：存放所有的事件类，也就是所有继承于 \Tiny\Event的类均放置于此文件夹中，事件的使用方一般是api与module；
3. module：存放公共模块，相对独立的逻辑，每个系统的公共逻辑均放于Module中，module之间可以相互调用，modulek可以调用db层代码。
4. db：数据库接口层，所有数据库的原始接口均封装于此层，db了调用数据库自己的访问接口外，不能调用其他接口，db之间不能相互调用，一般情况一个Mongodb的集合或者一张sql的表就对应db层中的一个类。

## cli
命令行执行工具，可以方便实现数据库管理的操作或者运维的操作。由于cli执行的命令大多需要调用php服务器中的接口，所以在实际项目中可以直接使用软链接实现。   
一个命令必须继承自\Tiny\CLI，并且在CLI命名空间中，类名去掉CLI\的部分就是命令名(使用/分割命名空间)，比如：类 CLI\Demo 的命令名为 Demo。

## tick
时钟源，每隔一定时间请求一固定接口，产生定时器事件。




