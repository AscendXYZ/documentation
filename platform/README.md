
#AscendXYZ Platform Documentation

The goal of this documentation is to give an insight into the architecture of the AscendXYZ Platform for internal and external reviews.

The platform is running on Microsoft Azure where the core developer and software stack is created with .NET and C#.

## Infrastructure
The infrastructure is provided with Microsoft Azure, except for a few scientist lab machines at the HQ, and everything is designed to be scale dynamic against the scalability targets of the used Azure Services. 

The core platform is build on Azure Cloud Services, Web and Worker Roles. A WebRole is used to host multiply Rest APIS with Azure AutoScale and Azure load balancing enabled ensuring that every user has a experience of the sites being responsive and fast.

Worker roles are used for longer processing tasks that can be offloaded from the Rest API to also ensuring that the API is responsive.

### Web Roles
There is deployed a WebRole with all the REST APIS that also has enabled Load Balancing and AutoScale. We have build scripts that makes it easy to setup deployment of AspNet websites into these existing WebRoles. The WebRoles are taking care of setting up IIS with the website stored in Blob Storage.

### Worker Roles 


As part of the core platform there are backend worker roles for message processing targeting different machine sizes depending on tasks. Development on these are part of the core platform and developers are given a simple message/message handler abstraction to implement, and as soon the message type is put on the processing queues, the associated message handler is triggered for the given message to carry out its task.

#### Common Worker
There is at all times running at least 2 Extra Small Instances (768MB Ram / 1 Shared Cpu) in each region and up to 50 Instances targeting 200 Messages per Machines. The responsibility of the core workers are to dispatch other workloads and sending notifications as emails/sms and deploying other cloud services.

When working with tiled maps as AscendXYZ does, having a lot of small compute notes enable quick response time on large REST based operations against Azure Services. Like moving a lot of small files around on Azure Blob Storage, using only one machine this is bound to latency on putting the copy commands on blob storage, where using a network of nodes allow to dispatch them easily at a higher throughput. 

#### Data Workers
There is also a Data Worker target that uses Small Instances (1.75GB Ram / 1 CPU ) but otherwise works in the same way as for the Common Worker. This is for more bandwidth or memory intensive tasks and the targeting per machine is much lower. This is only deployed (by the common worker) whenever there is something in the data worker queue.

#### Others
Larger machines can be deployed dynamic like data workers if needed, but we encourage our developers to implement their tasks if they require larger resources to use our algorithm platform.

### Algorithm Platform

The algorithm platform is build on the same principals as the message/message handler abstraction using dynamic deployed machines when something is in the queue. There exists queue for each machine configuration we need, ranging from 1.75 GB Ram to 128GB Ram, 1 to 32 CPU Cores and also SSD disks. So if a developer finds that one of the existing configuration is not fitting for his tasks, we will find out what configuration is needed for the given task and create this. Possible configurations can be found at the Azure Documentation.

We also has the options to run the Algorithm Service on premise if the needed hardware cannot be provisioned in the cloud.

The algorithm platform packs everything into a REST API Service, that allows developers to queue and chain tasks, and the platform takes care of deploying the needed machines if they are not already running. The platform also takes care of destroying machines if they have run idle for an hour.

#### Algorithms
Algorithms are developed as singleton packages that may require dependencies like GDAL,OpenCV or Python currently, this is something we want to extend to those frameworks that our data scientist team uses, enabling them to work with the tools that they feel they are most productive in.  

This also ensures that our core platform is not slowed down by large dependency packs like those above which also ensures higher maintainability since these packages can be upgraded out of the core release cycles.

Every algorithm developer is able to upload algorithms within the AscendXYZ Portal and maintain these. Each algorithm has its own REST endpoint for queuing, execution and status reporting. The goal is simply, to easily enable routine tasks from a scientist to be run and integrated in larger solutions from REST endpoints.

Algorithms are uploaded as zip packages with the compiled code or scripts together with a algspec file that has all the information about input and output parameters and which framework to use for execution.




##Rest APIS
All Rest APIS are build ontop of open source Asp.Net WebAPI.

##Portal 
The Ascend Portal is build as Single Page Application using tools like Grunt for packaging and deployment onto the webroles introduced above. The portal is using the following Open Source javascript libraries at its core:
1. RequireJS
2. KnockoutJS
3. JQuery

and then a bunch of other smaller libraries. 
For mapping we uses OpenLayers3 and Cesium


