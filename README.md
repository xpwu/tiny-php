# tiny-php

tiny-php 是一个为PHP写服务的一些基础库，在此基础库上可以方便的写服务逻辑，使用库的集成需要使用[phpinte](https://github.com/xpwu/php-integrate) 1.0版本来集成项目.


### <a name="TinyCore"></a>TinyCore
本部分主要是Tiny的一些基础库，其中最重要的是OperationConfig的提供，可以方便的生成统一的配置文件模板，需要在项目集成时加入生成配置文件模板的注解处理器。生成的模板路径是 build/inte/annotation/src/operation_config.php  
支持生成的配置文件分组显示，可以使用ConfigGroup注解定义一个分组，定义配置时extends此分组即可。


### <a name="TinyDBIndex"></a>TinyDBIndex
数据库索引创建的注解，与[CLI](#CLI)中的CreateIndex 使用相对应。同时提供了DBIndexDeprecated做原来的兼容。


### <a name="CLI"></a>TinyCLI
写CLI逻辑的基础库，一个cli命令必须继承自\Tiny\CLI。


### <a name="API"></a>TinyAPI
接口必须继承自\Tiny\API 或者其子类，比如\Tiny\JsonApi(加入了json的编解码)，并实现run方法，子类的命名空间与类名无规定，但是整个完整类名也就是接口名。比如：NS\SubAPI 的类名的接口名就是/NS/SubAPI。接口对应于请求中URI去掉参数的部分，比如：127.0.0.1:10000/MyProject/GetInfo, 会自动调用 MyProject\GetInfo的run方法。   
\Tiny\API还有两个辅助方法：beforeRun afterRun，可在run执行的前后做一些处理，比如JsonApi 就用于编解码工作。   
API的请求参数用Request对象传递，其中data就是POST的数据；处理的结果使用Response传递，其中的data就是返回的数据。  
  
错误日志的位置在php.ini的`error_log`项目配置，如果没有配置此项，默认为phar同级的error.log文件。

##### <a name="Config"></a>配置
operation_config.php文件的加载需要在php.ini中配置为`auto_prepend_file`的参数。php-fpm在启动时也可以使用-d参数修改`auto_prepend_file`的值。在nginx环境中也可以使用如下指令修改`auto_prepend_file`的值。单个值：

```
fastcgi_param PHP_VALUE "auto_prepend_file=/home/www/h1.php";
```
多个值(`\n`)分割：

```
fastcgi_param PHP_VALUE "auto_prepend_file=/home/www/h1.php \n auto_append_file=/home/www/h2.php";
```

##### <a name="Log"></a>日志
API的日志默认使用了log4php，由TinyLog4PHPAdapter库提供，需要在项目中添加该库的依赖。在API生成的配置项中有日志的配置，可以按照配置说明换成其他日志系统。如果使用TinyLog4PHPAdapter库，需要同时保证Log4PHP的三方库能按照phpinte1.0的要求进行加载。


### <a name="Event"></a>TinyEvent
事件相关逻辑，增加命名的事件中心，不同名字的事件中心是隔离的，相同的监听者监听相同的事件放入不同名字的事件中心不会相互干扰。定义一个\Tiny\Event的子类即定义了一个新的事件，事件参数由各子事件决定，在调用父类的构造函数时，需要指定要参与事件区分的参数，如果没有参数参与事件区分，就不需要传入任何参数。  
1.0相对于之前的代码做了修改，部分原来的接口提供了新的调用方式，同时兼容了原来的接口，但需要尽快升级。部分接口不再兼容，需要修改，在[升级](#Upgrade)中有说明。原来的定时器事件已移除，此部分用单独的服务来实现可能更合适。动态添加事件的功能后续版本提供。


##### 事件实现方式

采用Event-Listener模式实现事件机制。 
 
1. Listener注册  
Listener注册到事件中心(EventCenter)目前仅支持自动注册：使用Tiny\Event\Center\Annotation\AutoRegistrator注解一个类，实现要求的方法。在addListeners中使用EventCenter提供的addListenerxxx方法注册，在添加时，可以指定ListenMode，指明是否使用事件参数，如果指定为不使用，则对改事件类型所有参数生成的事件都感兴趣。
2. Listener使用   
定义一个继承自Listener的子类，实现handler方法，即定义了一个Listener，一个Listener只能监听一个具体的Event，在Listener的构造函数中指定监听的具体Event。
3. 事件的使用   
定义一个\Tiny\Event的子类即定义了一个新的事件，事件参数由各子事件决定，在调用父类的构造函数时，需要指定要参与事件区分的参数，如果没有参数参与事件区分，就不传入参数。 
  
```
class DemoEvent extends Event {
	function __construct(int $index, int $any) {
		parent::__construct(ScalarArg::int($index));
 	}

	public function getIndex() {
		return $this->index_;
	}

	private $index_;
}  

```
对于以上Event，`new DemoEvent(3, 5)`与`new DemoEvent(4, 5)`是两个不同的事件，但是`new DemoEvnet(3, 5)`与`new DemoEvent(3, 10)`是两个相同的事件。Listener可以监听一个具体参数的事件，如果要监听此事件所有参数生成的事件，在addListenerxxx方法注册时，使用ListenMode::notUseEventArgs()即可。

```
class AutoRegistrator implements \Tiny\Event\Center\Annotation\AutoRegistrator {

  function registerToEventCenter(): EventCenter {
    return EventCenter::default();
  }

  function addListeners(EventCenter $eventCenter): void {
    $eventCenter->addListener(new SubsListener(
      new DemoEvent(7, 9));
      
    $eventCenter->addListenerWithMode(new Sub2Listener(new DemoEvent(5, 15)), ListenMode::notUseEventArgs());
  }
}
```

自动注册一个监听者，监听第一个参数为7的DemoEvent事件(第二个参数9未参与事件区分)；
自动注册一个监听者，监听DemoEvent所有参数的事件。

当`new DemoEvent(7, 10)`事件产生时，SubListener 与 Sub2Listener 都将接收到事件，但当`new DemoEvent(5, 10)`事件产生时，只有Sub2Listener 能接收到事件。  
  
4. 普通事件产生  
Tiny\Event\EventCenter::byName(name)->postEvent($event);即可把事件发布到name命名的事件中心。


### <a name="Upgrade"></a>升级
由之前的版本升级到1.0版本可能需要做如下处理：  
1.工程准备：  
把原来的project 文件夹定义为源代码文件夹，或者直接替换为src类似的文件夹名，conf与mk文件在新的版本中不再使用；原来tiny相关的文件都可删除；在项目的根目录新建project.conf.hphp文件并按照要求配置。  
2.修改Event中的构造函数为新的版本。  
3.配置文件的修改。




