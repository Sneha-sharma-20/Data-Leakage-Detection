### Problem Statement

Data leakage is a critical challenge faced by organizations, leading to the compromise of sensitive information, financial loss, and reputational damage. In multi-agent systems, where data is distributed among multiple entities, it becomes difficult to trace the origin of a leak. Existing methods often lack the precision or efficiency required to identify the responsible agent, especially when dealing with large datasets and complex workflows.

This project addresses the problem by developing a **Data Leakage Detection System** designed to allocate sensitive data and unique alterations to agents and monitor their usage. In case of a leak, the system identifies the source by comparing the leaked data and its alteration with stored records. This approach ensures accountability while safeguarding organizational data.

The system is implemented as a web application with a Node.js backend and a dynamic HTML frontend, providing an intuitive interface for managing agents, allocating data, and performing leakage detection. The solution is scalable, memory-efficient, and easily integrates with existing data workflows, enabling organizations to enhance their data governance and security practices effectively.
