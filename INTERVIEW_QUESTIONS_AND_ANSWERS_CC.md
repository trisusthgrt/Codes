# CodeConnect - Comprehensive Interview Questions & Answers

## Table of Contents
1. [Project Experience Questions](#project-experience-questions)
2. [Project Overview](#project-overview)
3. [Architecture Questions](#architecture-questions)
4. [Backend Questions](#backend-questions)
5. [Frontend Questions](#frontend-questions)
6. [Real-time Communication Questions](#real-time-communication-questions)
7. [Code Editor Questions](#code-editor-questions)
8. [Code Execution Questions](#code-execution-questions)
9. [Security Questions](#security-questions)
10. [Performance Questions](#performance-questions)
11. [Testing Questions](#testing-questions)
12. [Deployment Questions](#deployment-questions)
13. [Best Practices & Improvements](#best-practices--improvements)

---

## Project Experience Questions

### Q: What was your project all about?

**Answer:** CodeConnect is a real-time collaborative code editor platform that enables multiple developers to work together on code simultaneously, similar to Google Docs but for programming. The project allows users to:

- Create or join coding rooms using unique room IDs
- Edit code collaboratively in real-time with instant synchronization
- See who else is in the room with visual user presence indicators
- Execute code in multiple programming languages (JavaScript, TypeScript, Python, C#) and see results instantly
- Share room IDs to invite others for pair programming or code reviews

The core value proposition is enabling seamless remote collaboration for coding interviews, pair programming sessions, code reviews, and educational purposes where multiple people need to work on code together in real-time.

### Q: What was the business need to go for the implementation / doing this project?

**Answer:** The business need for CodeConnect stemmed from several real-world challenges:

1. **Remote Collaboration:** With the rise of remote work and distributed teams, there was a need for a tool that allows developers to collaborate on code in real-time without the overhead of setting up complex development environments or screen sharing.

2. **Technical Interviews:** Companies conduct remote coding interviews where interviewers and candidates need to see and edit code simultaneously. Existing solutions were either too complex or lacked real-time collaboration features.

3. **Educational Platforms:** Coding bootcamps, online courses, and mentorship programs needed a platform where instructors and students could code together in real-time, making learning more interactive and engaging.

4. **Code Review Efficiency:** Traditional code review processes involve asynchronous pull requests. CodeConnect enables live code reviews where reviewers can make suggestions and see changes in real-time, significantly speeding up the review process.

5. **Pair Programming:** Distributed teams needed a tool that replicates the in-person pair programming experience, allowing two developers to work on the same codebase simultaneously with full visibility.

6. **Cost-Effective Solution:** Building an in-house solution was more cost-effective than licensing expensive enterprise collaboration tools, and it could be customized to specific organizational needs.

The project addressed the gap in the market for a lightweight, easy-to-use, real-time collaborative coding environment that doesn't require complex setup or authentication.

### Q: Did you complete the whole project yourself?

**Answer:** No, I did not complete the whole project myself. CodeConnect was developed as a team effort, which allowed us to leverage each team member's strengths and deliver a more robust solution. I believe in collaborative development and working as part of a team, as it brings diverse perspectives, better code quality through code reviews, and faster development through parallel work streams.

### Q: If no, what was your part in the whole project?

**Answer:** I was responsible for the **Backend Development and Real-time Communication Module**. My specific contributions included:

#### 1. **Backend Server Architecture (server.js)**
   - Designed and implemented the Express.js server that serves the React frontend and handles WebSocket connections
   - Set up the HTTP server with Socket.io integration
   - Implemented static file serving for the production React build
   - Configured the catch-all route to support React Router's client-side routing

#### 2. **Socket.io Real-time Communication System**
   - Implemented the complete WebSocket communication layer using Socket.io
   - Created the room-based collaboration system where users can join rooms and collaborate
   - Built the `userSocketMap` system to track socket IDs to usernames mapping
   - Implemented the `getAllConnectedClients()` function to retrieve all users in a room

#### 3. **Event Handlers Implementation**
   - **JOIN Event:** Handled user joining rooms, storing user information, and notifying all room members
   - **CODE_CHANGE Event:** Implemented real-time code synchronization by broadcasting code changes to all room members (excluding the sender to prevent loops)
   - **SYNC_CODE Event:** Built the code synchronization mechanism for newly joined users to receive the current code state
   - **DISCONNECT Event:** Implemented proper cleanup when users leave, including notifying other users and removing user data

#### 4. **Room Management System**
   - Designed the room-based architecture where each room is identified by a unique UUID
   - Implemented room joining/leaving logic using Socket.io's built-in room functionality
   - Ensured proper isolation between different rooms

#### 5. **Actions Constants Module (Actions.js)**
   - Created a centralized constants file for all Socket.io event names
   - Ensured consistency between frontend and backend event naming
   - Made the codebase more maintainable and less prone to typos

#### 6. **Integration with Frontend Team**
   - Worked closely with frontend developers to define the Socket.io event contract
   - Ensured proper data structure for events (roomId, username, code, socketId)
   - Collaborated on error handling and connection management strategies

#### 7. **Code Quality and Best Practices**
   - Implemented proper error handling for socket connections
   - Added console logging for debugging and monitoring
   - Ensured clean code structure and separation of concerns

**What I Did NOT Work On:**
- Frontend React components and UI development
- CodeMirror editor integration
- Code execution API integration (Piston API)
- Styling and CSS
- Home page and routing logic
- User interface design

### Q: What difficulties did you face while doing your part of the project?

**Answer:** I encountered several challenges during backend development:

#### 1. **Real-time Code Synchronization Issues**
   **Problem:** Initially, when a user typed code, it would create an infinite loop where the change would be sent to the server, broadcasted back, received by the sender, and trigger another change event.

   **Solution:** I implemented two key fixes:
   - Used `socket.to(roomId)` instead of `io.to(roomId)` to exclude the sender from receiving their own changes
   - Added origin checking in the frontend to prevent emitting events when code is set programmatically (not from user input)

#### 2. **Code Synchronization for New Joiners**
   **Problem:** When a new user joined a room, they would see an empty editor even though other users had code. The initial implementation didn't handle state synchronization properly.

   **Solution:** I implemented the `SYNC_CODE` event mechanism where:
   - When a user joins, all existing clients receive the new user's socketId
   - Existing clients emit `SYNC_CODE` with the current code to the new user
   - The new user receives the code and updates their editor
   - This ensures new joiners always see the current state

#### 3. **User Tracking and Cleanup**
   **Problem:** When users disconnected unexpectedly (network issues, browser close), their entries remained in `userSocketMap`, causing memory leaks and incorrect user lists.

   **Solution:** I implemented proper cleanup in the `disconnecting` event handler:
   - Captured all rooms the socket was in before disconnection
   - Notified all room members about the disconnection
   - Removed the user from `userSocketMap`
   - Ensured socket properly leaves all rooms

#### 4. **Room Management Complexity**
   **Problem:** Initially, I wasn't sure how to efficiently track which users were in which rooms and retrieve that information.

   **Solution:** I leveraged Socket.io's built-in room functionality:
   - Used `socket.join(roomId)` and `socket.leave(roomId)` for room management
   - Utilized `io.sockets.adapter.rooms.get(roomId)` to get all sockets in a room
   - Combined this with `userSocketMap` to get both socket IDs and usernames

#### 5. **Frontend-Backend Event Contract**
   **Problem:** Early in development, there were mismatches between frontend and backend event names and data structures, causing communication failures.

   **Solution:** I created the `Actions.js` constants file and worked closely with the frontend team to:
   - Define a clear event contract
   - Ensure consistent event naming
   - Standardize data structures for all events
   - Document expected payloads for each event

#### 6. **Handling Concurrent Connections**
   **Problem:** When multiple users joined simultaneously or made rapid code changes, the server would sometimes process events out of order or miss some updates.

   **Solution:** I ensured that:
   - Each socket connection is handled independently
   - Events are processed in the order they're received
   - Room broadcasts are atomic operations
   - Added proper error handling to prevent crashes from malformed events

#### 7. **Debugging Real-time Issues**
   **Problem:** Debugging WebSocket communication is challenging because events happen asynchronously and it's hard to trace the flow.

   **Solution:** I added strategic console.log statements and worked with the team to:
   - Log all major events (join, code change, disconnect)
   - Include relevant context (roomId, username, socketId) in logs
   - Test scenarios with multiple browser tabs to simulate multiple users
   - Use browser DevTools and server logs together to trace issues

#### 8. **Integration Challenges**
   **Problem:** Ensuring the backend worked seamlessly with the frontend team's implementation, especially when they were developing in parallel.

   **Solution:** I maintained open communication:
   - Regular sync meetings to discuss progress and blockers
   - Shared API/event documentation
   - Created mock event handlers for frontend testing
   - Tested integration frequently as features were developed

These challenges taught me valuable lessons about real-time systems, debugging asynchronous code, and the importance of clear communication in team projects.

### Q: What technologies did you use and why did you use only those technologies?

**Answer:** For my backend responsibilities, I used the following technologies:

#### 1. **Node.js**
   **Why:** 
   - JavaScript runtime that allows using the same language (JavaScript) for both frontend and backend, reducing context switching
   - Excellent performance for I/O-intensive operations like WebSocket connections
   - Large ecosystem of packages (npm)
   - Non-blocking, event-driven architecture perfect for real-time applications

#### 2. **Express.js**
   **Why:**
   - Lightweight, minimal web framework for Node.js
   - Simple API for routing and middleware
   - Easy to set up and configure
   - Well-documented and widely used in the industry
   - Perfect for serving static files and handling basic HTTP requests
   - Minimal overhead, which is important for real-time applications

#### 3. **Socket.io**
   **Why:**
   - Industry-standard library for real-time bidirectional communication
   - Built-in room management functionality (perfect for our room-based collaboration)
   - Automatic reconnection handling
   - Cross-browser compatibility (falls back to polling if WebSocket unavailable)
   - Event-based API that's intuitive and easy to work with
   - Excellent documentation and community support
   - Handles connection management, heartbeats, and error recovery automatically

#### 4. **HTTP Module (Node.js built-in)**
   **Why:**
   - Socket.io requires an HTTP server instance
   - Native Node.js module, no additional dependencies
   - Lightweight and performant

#### 5. **Path Module (Node.js built-in)**
   **Why:**
   - For handling file paths when serving static React build files
   - Cross-platform path handling
   - Native module, no dependencies

**Why NOT Other Technologies:**
- **Not using a database (MongoDB/PostgreSQL):** Initially, we didn't need persistence - rooms were ephemeral. Adding a database would add complexity without immediate benefit.
- **Not using Redis:** For a single-server deployment, Socket.io's in-memory adapter was sufficient. Redis would be needed only for horizontal scaling.
- **Not using TypeScript:** The team was more comfortable with JavaScript, and the project scope didn't require the added complexity of TypeScript setup.
- **Not using a framework like Nest.js:** Express was sufficient for our needs. Nest.js would be overkill for a simple real-time server.
- **Not using GraphQL:** Our real-time needs were better served by Socket.io's event-based model than GraphQL subscriptions.

**Technology Selection Philosophy:**
I chose technologies based on:
1. **Simplicity:** Technologies that are easy to understand and maintain
2. **Suitability:** Best fit for real-time collaboration requirements
3. **Team Familiarity:** Technologies the team was comfortable with
4. **Performance:** Lightweight solutions that don't add unnecessary overhead
5. **Scalability Path:** Technologies that can scale when needed (Socket.io supports Redis adapter for multi-server)

The technology stack was intentionally minimal to reduce complexity, improve maintainability, and allow the team to focus on core functionality rather than fighting with complex frameworks.

### Q: How long did it take to complete your part of the project?

**Answer:** The backend development and real-time communication module took approximately **3-4 weeks** to complete, working part-time alongside other commitments. Here's the breakdown:

#### Week 1: Planning and Setup
- **Days 1-2:** Research and architecture design
  - Studied Socket.io documentation
  - Designed room-based collaboration model
  - Planned event structure and data flow
- **Days 3-4:** Initial setup
  - Set up Express server
  - Integrated Socket.io
  - Created basic connection handling
  - Set up project structure

#### Week 2: Core Functionality
- **Days 1-3:** Room management and user tracking
  - Implemented JOIN event handler
  - Built userSocketMap system
  - Created getAllConnectedClients function
  - Implemented user presence notifications
- **Days 4-5:** Code synchronization
  - Implemented CODE_CHANGE event
  - Fixed infinite loop issues
  - Added code broadcasting logic

#### Week 3: Synchronization and Edge Cases
- **Days 1-2:** Code sync for new joiners
  - Implemented SYNC_CODE event
  - Fixed state synchronization issues
  - Tested with multiple users
- **Days 3-4:** Disconnection handling
  - Implemented disconnecting event handler
  - Added proper cleanup logic
  - Fixed memory leak issues
- **Day 5:** Integration testing with frontend team

#### Week 4: Refinement and Bug Fixes
- **Days 1-2:** Bug fixes and edge case handling
  - Fixed concurrent connection issues
  - Improved error handling
  - Added logging for debugging
- **Days 3-4:** Code cleanup and documentation
  - Refactored code for better structure
  - Added comments and documentation
  - Created Actions.js constants file
- **Day 5:** Final testing and deployment preparation

**Total Effort:** Approximately **80-100 hours** of focused development work.

**Factors Affecting Timeline:**
- Learning curve for Socket.io (first time using it extensively)
- Debugging real-time synchronization issues
- Integration coordination with frontend team
- Testing with multiple users and scenarios
- Iterative improvements based on feedback

The timeline could have been shorter with more Socket.io experience, but the learning process was valuable and resulted in a deeper understanding of real-time systems.

### Q: Did you need help from people working on the other modules?

**Answer:** Yes, absolutely! Collaboration was essential for the project's success. Here are the key areas where I needed help and how we worked together:

#### 1. **Frontend Integration Support**
   **What I Needed:**
   - Understanding of how the frontend would emit events and what data structure they expected
   - Testing the Socket.io connection from the frontend side
   - Verifying that events were being received correctly on the frontend

   **How They Helped:**
   - The frontend team shared their Socket.io client implementation
   - We tested events together using browser DevTools
   - They provided feedback on event payload structures
   - We debugged connection issues together

#### 2. **Event Contract Definition**
   **What I Needed:**
   - Agreement on event names and data structures
   - Understanding of when events should be emitted
   - Clarity on error handling expectations

   **How We Collaborated:**
   - Regular meetings to discuss event contracts
   - Created shared documentation of all events
   - Both teams reviewed and agreed on the Actions.js constants
   - We maintained a shared document with event specifications

#### 3. **Testing Support**
   **What I Needed:**
   - Multiple users to test real-time collaboration
   - Testing different scenarios (rapid typing, multiple joiners, disconnections)
   - UI feedback to verify backend events were working

   **How They Helped:**
   - Frontend team provided test scenarios
   - We did joint testing sessions with multiple browser tabs
   - They reported UI issues that helped identify backend problems
   - We used their UI to verify that events were being processed correctly

#### 4. **Code Execution Integration**
   **What I Needed:**
   - Understanding of how code execution would work
   - Whether backend needed to handle code execution or if it was frontend-only

   **How They Helped:**
   - The team member working on code execution explained it was frontend-only (using Piston API)
   - This helped me understand that backend only needed to handle code synchronization
   - We discussed if we needed to store execution results (decided against it initially)

#### 5. **UI/UX Feedback**
   **What I Needed:**
   - Understanding of user experience requirements
   - Feedback on connection status and error messages
   - Input on user presence display

   **How They Helped:**
   - UI/UX team provided requirements for user presence
   - They suggested improvements to error handling messages
   - We discussed what information should be shown to users (usernames, connection status)

#### 6. **Deployment Coordination**
   **What I Needed:**
   - Understanding of deployment environment
   - Configuration for production (ports, CORS, etc.)
   - Environment variables setup

   **How We Collaborated:**
   - DevOps/Deployment team helped with server configuration
   - We discussed CORS settings together
   - Coordinated on environment variables (REACT_APP_BACKEND_URL)
   - Tested deployment together

#### 7. **Problem Solving Together**
   **What I Needed:**
   - Debugging help when issues arose
   - Second opinions on architecture decisions
   - Code review and feedback

   **How We Collaborated:**
   - Regular stand-up meetings to discuss blockers
   - Pair debugging sessions when issues were complex
   - Code reviews where team members suggested improvements
   - Brainstorming sessions for solving difficult problems

**Key Collaboration Practices:**
- **Daily Stand-ups:** Brief meetings to sync progress and identify blockers
- **Shared Documentation:** Maintained docs for API contracts and event structures
- **Pair Programming:** Occasional pair sessions for complex features
- **Code Reviews:** Team members reviewed each other's code
- **Testing Together:** Joint testing sessions to verify integration
- **Open Communication:** Slack/Teams channel for quick questions and updates

**What This Taught Me:**
Working as part of a team taught me:
- The importance of clear communication and documentation
- How to define and maintain API contracts
- The value of code reviews and collaborative problem-solving
- How to balance independence with collaboration
- The importance of being available to help others when they need it

This collaborative approach not only improved the code quality but also made the development process more enjoyable and educational. I believe that the best software is built by teams working together, not in isolation.

---

## Project Overview

### Q1: What is CodeConnect and what does it do?

**Answer:** CodeConnect is a real-time collaborative code editor application that allows multiple users to edit code together in shared rooms. It supports multiple programming languages (JavaScript, TypeScript, Python, C#) and provides real-time code synchronization, user presence indicators, and code execution capabilities. Users can create or join rooms using unique room IDs and collaborate on code in real-time.

### Q2: What are the main technologies used in this project?

**Answer:**
- **Backend:** Node.js, Express.js, Socket.io
- **Frontend:** React 17, React Router, CodeMirror, Socket.io-client
- **Code Execution:** Piston API (external service)
- **UI Libraries:** React Hot Toast, React Avatar
- **Build Tool:** Create React App (react-scripts)
- **Package Manager:** npm

---

## Architecture Questions

### Q3: Describe the overall architecture of CodeConnect.

**Answer:** CodeConnect follows a client-server architecture with real-time bidirectional communication:

1. **Frontend (React SPA):** Single-page application that handles UI, user interactions, and connects to the backend via WebSocket
2. **Backend (Express + Socket.io):** 
   - Express server serves static React build files
   - Socket.io handles real-time WebSocket connections
   - Manages room-based collaboration and user presence
3. **External Service:** Piston API for code execution

The architecture is event-driven, using Socket.io events for real-time synchronization of code changes, user joins/leaves, and room management.

### Q4: How does the frontend communicate with the backend?

**Answer:** The frontend uses two communication methods:
1. **WebSocket (Socket.io):** Primary communication channel for real-time features:
   - Code synchronization
   - User presence (join/leave events)
   - Room management
2. **HTTP (Axios):** Used for code execution via external Piston API

The Socket.io connection is established using `initSocket()` which creates a persistent WebSocket connection with reconnection capabilities.

### Q5: Explain the room-based collaboration model.

**Answer:** The application uses a room-based model where:
- Each room has a unique ID (UUID v4)
- Users join rooms by providing a room ID and username
- All users in the same room see synchronized code changes in real-time
- The backend maintains a `userSocketMap` to track which socket ID belongs to which username
- When a user joins, all clients in the room are notified via the `JOINED` event
- Code changes are broadcast to all other users in the room (excluding the sender)

---

## Backend Questions

### Q6: Explain the backend server structure (server.js).

**Answer:** The backend server (`server.js`) has the following structure:

1. **Express Setup:** Creates HTTP server and Express app
2. **Static File Serving:** Serves React build files and handles SPA routing
3. **Socket.io Integration:** Creates Socket.io server instance
4. **User Management:** Maintains `userSocketMap` to track socket-to-username mapping
5. **Room Management:** Uses Socket.io's built-in room functionality
6. **Event Handlers:**
   - `JOIN`: User joins a room
   - `CODE_CHANGE`: Broadcasts code changes to room members
   - `SYNC_CODE`: Synchronizes code for newly joined users
   - `disconnecting`: Handles user disconnection

### Q7: What is the purpose of `userSocketMap`?

**Answer:** `userSocketMap` is an object that maps socket IDs to usernames. It serves to:
- Track which username is associated with each socket connection
- Display usernames in the connected clients list
- Notify other users when someone joins or leaves with their username
- Maintain user identity across socket reconnections

**Code:** `userSocketMap[socket.id] = username;`

### Q8: How does `getAllConnectedClients` function work?

**Answer:** This function retrieves all clients connected to a specific room:

```javascript
function getAllConnectedClients(roomId) {
    return Array.from(io.sockets.adapter.rooms.get(roomId) || []).map(
        (socketId) => {
            return {
                socketId,
                username: userSocketMap[socketId],
            };
        }
    );
}
```

It:
1. Gets all socket IDs in the room using `io.sockets.adapter.rooms.get(roomId)`
2. Converts the Set to an Array
3. Maps each socket ID to an object containing both socketId and username
4. Returns the list of all connected clients with their usernames

### Q9: Explain the JOIN event handler flow.

**Answer:** When a user joins a room:

1. Client emits `ACTIONS.JOIN` with `{ roomId, username }`
2. Server stores username in `userSocketMap[socket.id]`
3. Server adds socket to the room: `socket.join(roomId)`
4. Server gets all connected clients in the room
5. Server emits `ACTIONS.JOINED` to **all clients in the room** (including the new joiner)
6. Each client receives the full list of clients, username, and socketId
7. New client can then request code sync via `ACTIONS.SYNC_CODE`

### Q10: Why does the CODE_CHANGE event use `socket.to(roomId)` instead of `io.to(roomId)`?

**Answer:** `socket.to(roomId)` broadcasts to all clients in the room **except the sender**, preventing the sender from receiving their own changes back. This avoids:
- Infinite loops
- Unnecessary re-renders
- Duplicate change events

If `io.to(roomId)` was used, the sender would receive their own change, causing the editor to update unnecessarily.

### Q11: How does code synchronization work for newly joined users?

**Answer:** When a new user joins:

1. After receiving `ACTIONS.JOINED`, the client emits `ACTIONS.SYNC_CODE` with the current code and the new user's socketId
2. Server receives `ACTIONS.SYNC_CODE` and emits `ACTIONS.CODE_CHANGE` directly to that specific socketId
3. The new user's editor receives the current code and updates their editor
4. This ensures new users see the existing code immediately upon joining

**Note:** The current implementation has the new user request sync, but ideally the server should proactively send code to new joiners.

### Q12: How is user disconnection handled?

**Answer:** The `disconnecting` event handler:

1. Gets all rooms the socket is in
2. Emits `ACTIONS.DISCONNECTED` to all other clients in those rooms
3. Removes the socket from `userSocketMap`
4. Socket automatically leaves all rooms

This ensures other users are notified when someone leaves and the UI updates accordingly.

### Q13: What is the purpose of serving static files in the backend?

**Answer:** The backend serves the React build files to:
1. **Production Deployment:** In production, React is built into static files that need to be served
2. **SPA Routing:** The catch-all route (`app.use((req, res, next) => {...})`) ensures all routes serve `index.html`, allowing React Router to handle client-side routing
3. **Single Server:** Allows running both frontend and backend from one server/port

### Q14: What are the ACTIONS constants and why are they used?

**Answer:** ACTIONS is a constants object defining all Socket.io event names:

```javascript
const ACTIONS = {
    JOIN: 'join',
    JOINED: 'joined',
    DISCONNECTED: 'disconnected',
    CODE_CHANGE: 'code-change',
    SYNC_CODE: 'sync-code',
    LEAVE: 'leave',
};
```

**Benefits:**
- Prevents typos in event names
- Makes refactoring easier
- Provides better IDE autocomplete
- Ensures consistency between frontend and backend
- Makes code more maintainable

---

## Frontend Questions

### Q15: Describe the React application structure.

**Answer:** The frontend is organized as:

```
src/
├── App.js              # Main app component with routing
├── pages/
│   ├── Home.js         # Landing page (room join/create)
│   └── EditorPage.js   # Main editor page
├── components/
│   ├── Editor.js       # CodeMirror editor component
│   └── Client.js       # User avatar component
├── socket.js           # Socket.io initialization
├── api.js              # Code execution API calls
├── Actions.js          # Socket event constants
└── constants.js        # Language versions and snippets
```

### Q16: How does React Router work in this application?

**Answer:** React Router v6 is used with:
- **Route `/`:** Renders `Home` component (room join/create)
- **Route `/editor/:roomId`:** Renders `EditorPage` with roomId from URL params
- **Navigation:** Uses `useNavigate()` hook to programmatically navigate
- **State Passing:** Username is passed via `location.state` when navigating

The router enables deep linking - users can share room URLs directly.

### Q17: Explain the Home component functionality.

**Answer:** The `Home` component allows users to:
1. **Create Room:** Generates UUID, sets it in state, shows toast, and navigates to editor
2. **Join Room:** Validates roomId and username, then navigates to editor
3. **Input Handling:** Supports Enter key to submit
4. **Auto-navigation:** After creating a room, automatically navigates to it

**State Management:**
- `roomId`: Current room ID input
- `username`: Current username input

### Q18: How does EditorPage manage state and side effects?

**Answer:** EditorPage uses multiple hooks:

**State:**
- `language`: Selected programming language
- `output`: Code execution output
- `clients`: List of connected users
- `socketRef`: Reference to socket instance
- `codeRef`: Reference to current code

**Effects:**
1. **Socket Initialization:** Sets up socket connection, event listeners, and cleanup
2. **Code Sync:** Listens for code changes from other users
3. **User Management:** Handles join/leave events

**Refs:**
- `socketRef`: Persists socket across re-renders
- `codeRef`: Stores code without causing re-renders

### Q19: Why use `useRef` for socket and code instead of `useState`?

**Answer:**
- **Socket (`socketRef`):** 
  - Socket instance doesn't need to trigger re-renders
  - Must persist across component re-renders
  - Used in event handlers that need stable reference
  
- **Code (`codeRef`):**
  - Code changes frequently (every keystroke)
  - Storing in state would cause excessive re-renders
  - Only needs to be read when executing or syncing

### Q20: Explain the socket initialization in EditorPage.

**Answer:** The socket initialization effect:

1. **Creates Connection:** Calls `initSocket()` to establish WebSocket
2. **Error Handling:** Listens for connection errors and navigates back on failure
3. **Joins Room:** Emits `ACTIONS.JOIN` with roomId and username
4. **Listens for JOINED:** Updates clients list and requests code sync
5. **Listens for DISCONNECTED:** Removes disconnected users from clients list
6. **Cleanup:** Disconnects socket and removes listeners on unmount

**Dependencies:** Empty array `[]` means it runs once on mount.

### Q21: How does the code execution feature work?

**Answer:** Code execution flow:

1. User clicks "RUN" button
2. `runCode()` function is called
3. Gets current code from `codeRef.current`
4. Calls `executeCode(language, code)` from `api.js`
5. Makes POST request to Piston API with language, version, and code
6. Receives response with stdout/stderr
7. Updates `output` state with result
8. Output is displayed in the output panel

**API:** Uses Piston API (`https://emkc.org/api/v2/piston`) for code execution.

### Q22: What is the purpose of the Client component?

**Answer:** The `Client` component displays a connected user:
- Uses `react-avatar` to generate avatar from username
- Shows username below avatar
- Rendered in a list for all connected clients
- Provides visual feedback of who is in the room

### Q23: How does the copy room ID feature work?

**Answer:** The `copyRoomId()` function:
1. Uses browser's Clipboard API: `navigator.clipboard.writeText(roomId)`
2. Shows success toast on success
3. Shows error toast on failure
4. Allows users to easily share room IDs

### Q24: Why is there a Navigate component check in EditorPage?

**Answer:** The check `if (!location.state)` redirects to home if:
- User directly accesses `/editor/:roomId` URL without going through Home
- Username wasn't passed via navigation state
- Prevents accessing editor without username

This ensures proper authentication flow (though basic - just username validation).

### Q25: Explain the language selection feature.

**Answer:** 
- Dropdown select allows choosing: JavaScript, TypeScript, Python, C#
- State stored in `language` state variable
- Used when executing code to specify which language runtime to use
- Language versions are defined in `constants.js` (`LANGUAGE_VERSIONS`)

**Note:** The editor mode doesn't change based on language selection - it always uses JavaScript mode in CodeMirror.

---

## Real-time Communication Questions

### Q26: How does Socket.io establish connection in this app?

**Answer:** Connection is established via `initSocket()`:

```javascript
const options = {
    'force new connection': true,
    reconnectionAttempt: 'Infinity',
    timeout: 24 * 60 * 60 * 1000,
    transports: ['websocket'],
};
return io(process.env.REACT_APP_BACKEND_URL, options);
```

**Options:**
- `force new connection`: Always creates new connection
- `reconnectionAttempt: 'Infinity'`: Keeps trying to reconnect forever
- `timeout`: 24-hour connection timeout
- `transports: ['websocket']`: Uses only WebSocket (no polling fallback)

### Q27: What happens when a user types code in the editor?

**Answer:** Real-time code change flow:

1. User types in CodeMirror editor
2. CodeMirror `change` event fires
3. Editor component gets new code value
4. Calls `onCodeChange(code)` callback (updates `codeRef.current`)
5. If change origin is not `'setValue'` (to avoid loops), emits `ACTIONS.CODE_CHANGE`
6. Server receives event and broadcasts to all other clients in room
7. Other clients receive `ACTIONS.CODE_CHANGE` event
8. Their editors update via `editorRef.current.setValue(code)`

### Q28: How does the app prevent infinite loops when syncing code?

**Answer:** Two mechanisms:

1. **Origin Check:** In Editor's change handler:
   ```javascript
   if (origin !== 'setValue') {
       socketRef.current.emit(ACTIONS.CODE_CHANGE, {...});
   }
   ```
   Only emits if change came from user input, not programmatic updates.

2. **Broadcast Exclusion:** Server uses `socket.to(roomId)` instead of `io.to(roomId)`, so sender doesn't receive their own change.

### Q29: What is the difference between `socket.emit()`, `socket.on()`, `io.emit()`, and `socket.to()`?

**Answer:**
- **`socket.emit()`:** Sends event from client to server (or server to specific client)
- **`socket.on()`:** Listens for events on a socket
- **`io.emit()`:** Server broadcasts to ALL connected clients
- **`socket.to(roomId)`:** Server broadcasts to all clients in room EXCEPT the sender
- **`io.to(roomId)`:** Server broadcasts to all clients in room INCLUDING the sender

### Q30: How does reconnection work if connection is lost?

**Answer:** Socket.io automatically handles reconnection:
- With `reconnectionAttempt: 'Infinity'`, it keeps trying
- On reconnect, the socket gets a new ID
- However, the current implementation doesn't handle reconnection gracefully:
  - User would need to rejoin the room
  - `userSocketMap` would have stale entries
  - Code state might be lost

**Improvement needed:** Handle reconnection by rejoining room and syncing state.

---

## Code Editor Questions

### Q31: What is CodeMirror and how is it integrated?

**Answer:** CodeMirror is a versatile text editor implemented in JavaScript:
- Provides syntax highlighting, line numbers, themes
- Used via `Codemirror.fromTextArea()` to convert textarea to editor
- Configured with:
  - Mode: JavaScript (though language can be changed)
  - Theme: Dracula
  - Auto-close tags and brackets
  - Line numbers enabled

### Q32: How is CodeMirror initialized in the Editor component?

**Answer:** Initialization happens in `useEffect`:

1. Gets textarea element by ID: `document.getElementById('realtimeEditor')`
2. Creates CodeMirror instance with configuration
3. Stores instance in `editorRef.current`
4. Sets up change listener to emit code changes
5. Listens for remote code changes and updates editor

**Note:** The textarea is just a placeholder - CodeMirror replaces it with its own DOM.

### Q33: Why is the editor initialized in a useEffect with `roomId` dependency?

**Answer:** The `roomId` dependency ensures:
- Editor is reinitialized when room changes
- Fresh editor instance for each room
- Prevents code from previous room persisting

However, this might cause issues if user navigates between rooms - editor would be recreated.

### Q34: What happens when code is received from another user?

**Answer:** When `ACTIONS.CODE_CHANGE` is received:
1. Socket listener in Editor component receives `{ code }`
2. Checks if code is not null
3. Updates editor: `editorRef.current.setValue(code)`
4. This triggers CodeMirror's change event
5. But the origin check prevents re-emitting (avoiding loop)

### Q35: What are the limitations of the current CodeMirror implementation?

**Answer:**
1. **Single Language Mode:** Always uses JavaScript mode regardless of selected language
2. **No Language Switching:** Editor mode doesn't change when language dropdown changes
3. **No Syntax Highlighting:** Other languages don't get proper highlighting
4. **Reinitialization:** Editor might be recreated unnecessarily
5. **No Cursor Position Sync:** Only code syncs, not cursor positions
6. **No Conflict Resolution:** No handling for simultaneous edits

---

## Code Execution Questions

### Q36: How does code execution work with Piston API?

**Answer:** Code execution flow:

1. **API Setup:** Axios instance configured with Piston API base URL
2. **Request:** POST to `/execute` with:
   - `language`: Selected language (javascript, python, etc.)
   - `version`: Language version from `LANGUAGE_VERSIONS`
   - `files`: Array with code content
3. **Response:** Returns `{ run: { stdout, stderr } }`
4. **Display:** Shows stdout or stderr in output panel

### Q37: What languages are supported and where are versions defined?

**Answer:** Supported languages (in `constants.js`):
- JavaScript: 18.15.0
- TypeScript: 5.0.3
- Python: 3.10.0
- Java: 15.0.2
- C#: 6.12.0
- PHP: 8.2.3

**Note:** Only JavaScript, TypeScript, Python, and C# are in the dropdown, but constants include more.

### Q38: What happens if code execution fails?

**Answer:** Current error handling:
- Try-catch block catches errors
- Logs error to console
- Doesn't show user-friendly error message
- Output state might remain empty or show previous output

**Improvement needed:** Better error handling and user feedback.

### Q39: Is code execution secure? What are the risks?

**Answer:** **Security Concerns:**
1. **No Input Validation:** Code is sent directly to external API without sanitization
2. **No Rate Limiting:** Users can execute code unlimited times
3. **External Dependency:** Relies on third-party service (Piston API)
4. **No Sandboxing:** Code runs on external server (though Piston likely sandboxes)
5. **No Authentication:** Anyone with room ID can execute code
6. **Resource Limits:** No control over execution time/memory limits

**Recommendations:**
- Add rate limiting
- Validate/sanitize code before execution
- Add execution timeout
- Consider self-hosted execution environment
- Add user authentication

---

## Security Questions

### Q40: What security vulnerabilities exist in this application?

**Answer:** Major security issues:

1. **No Authentication:** Anyone with room ID can join
2. **No Authorization:** No role-based access control
3. **XSS Risk:** Username and code are not sanitized before display
4. **No Input Validation:** Room IDs and usernames not validated
5. **No Rate Limiting:** Socket events and API calls not rate-limited
6. **CORS:** No explicit CORS configuration (relies on defaults)
7. **Environment Variables:** Backend URL in frontend (exposed in client)
8. **No HTTPS Enforcement:** No SSL/TLS requirement mentioned
9. **Socket.io Security:** No authentication middleware for socket connections
10. **Code Injection:** Code execution without proper sandboxing validation

### Q41: How would you add authentication to this application?

**Answer:** Implementation approach:

1. **Backend:**
   - Add JWT-based authentication
   - Create login/register endpoints
   - Add socket.io middleware to verify JWT on connection
   - Store user sessions

2. **Frontend:**
   - Add login/register pages
   - Store JWT in localStorage or httpOnly cookies
   - Send JWT with socket connection
   - Add protected routes

3. **Socket.io:**
   ```javascript
   io.use((socket, next) => {
       const token = socket.handshake.auth.token;
       // Verify JWT
       // Attach user info to socket
   });
   ```

### Q42: How can you prevent XSS attacks?

**Answer:** Prevention measures:

1. **Sanitize Inputs:**
   - Escape HTML in usernames before display
   - Use React's built-in escaping (already does this for text)
   - Sanitize code before execution

2. **Content Security Policy (CSP):**
   - Add CSP headers to restrict script execution
   - Prevent inline scripts

3. **Input Validation:**
   - Validate room IDs (UUID format)
   - Validate usernames (alphanumeric, length limits)
   - Sanitize code snippets

4. **Use Libraries:**
   - `DOMPurify` for HTML sanitization
   - `validator` for input validation

### Q43: How would you secure Socket.io connections?

**Answer:** Security measures:

1. **Authentication Middleware:**
   ```javascript
   io.use((socket, next) => {
       const token = socket.handshake.auth.token;
       // Verify and attach user
   });
   ```

2. **Origin Validation:**
   ```javascript
   const io = new Server(server, {
       cors: {
           origin: process.env.FRONTEND_URL,
           credentials: true
       }
   });
   ```

3. **Room Authorization:** Verify user has permission to join room
4. **Rate Limiting:** Limit events per socket per time period
5. **Input Validation:** Validate all socket event data
6. **Encryption:** Use WSS (WebSocket Secure) in production

---

## Performance Questions

### Q44: What performance issues exist in the current implementation?

**Answer:** Performance concerns:

1. **Code Sync Frequency:** Every keystroke sends full code (not diffs)
2. **No Debouncing:** Code changes emitted immediately
3. **Large Code Blocks:** Sending entire file on every change
4. **No Virtualization:** Client list could be long
5. **Memory Leaks:** Potential issues with event listeners
6. **No Code Compression:** Large code blocks sent uncompressed
7. **Re-renders:** EditorPage might re-render unnecessarily
8. **No Caching:** Code execution results not cached

### Q45: How would you optimize code synchronization?

**Answer:** Optimization strategies:

1. **Operational Transforms (OT) or CRDTs:**
   - Send only changes (diffs) instead of full code
   - Use libraries like ShareJS or Yjs

2. **Debouncing:**
   ```javascript
   const debouncedEmit = useMemo(
       () => debounce((code) => {
           socketRef.current.emit(ACTIONS.CODE_CHANGE, { roomId, code });
       }, 300),
       [roomId]
   );
   ```

3. **Throttling:** Limit emissions to N per second
4. **Compression:** Compress code before sending
5. **Batching:** Batch multiple changes together

### Q46: How would you handle large code files?

**Answer:** Strategies:

1. **Chunking:** Split large files into chunks
2. **Lazy Loading:** Load code on demand
3. **Virtual Scrolling:** For very long files in editor
4. **Incremental Updates:** Only send changed portions
5. **File Size Limits:** Enforce maximum file size
6. **Compression:** Compress before transmission

### Q47: What are potential memory leaks and how to fix them?

**Answer:** Memory leak sources:

1. **Event Listeners:** Not properly cleaned up
   ```javascript
   // Fix: Always cleanup
   return () => {
       socketRef.current.off(ACTIONS.CODE_CHANGE);
   };
   ```

2. **Socket Connections:** Not disconnected on unmount
   ```javascript
   // Fix: Disconnect in cleanup
   return () => {
       socketRef.current.disconnect();
   };
   ```

3. **Intervals/Timeouts:** Not cleared
4. **CodeMirror Instance:** Not destroyed
5. **Closures:** Holding references to large objects

**Best Practice:** Always cleanup in useEffect return function.

---

## Testing Questions

### Q48: How would you test this application?

**Answer:** Testing strategy:

1. **Unit Tests:**
   - Test utility functions
   - Test component rendering
   - Test state management
   - Use Jest + React Testing Library

2. **Integration Tests:**
   - Test socket communication
   - Test room joining flow
   - Test code synchronization
   - Use Socket.io testing utilities

3. **E2E Tests:**
   - Test full user flows
   - Multiple users collaborating
   - Use Cypress or Playwright

4. **Backend Tests:**
   - Test socket event handlers
   - Test room management
   - Test user tracking

### Q49: How would you test Socket.io functionality?

**Answer:** Testing approaches:

1. **Mock Socket.io:**
   ```javascript
   import { io } from 'socket.io-client';
   jest.mock('socket.io-client');
   ```

2. **Test Socket Events:**
   ```javascript
   const mockEmit = jest.fn();
   socketRef.current = { emit: mockEmit };
   // Test that emit is called with correct args
   ```

3. **Integration Testing:**
   - Use `socket.io-client` in tests
   - Connect to test server
   - Verify events are received

4. **Backend Testing:**
   ```javascript
   const client = io('http://localhost:5000');
   client.emit('join', { roomId: 'test', username: 'user' });
   // Verify response
   ```

### Q50: What test cases would you write for the Editor component?

**Answer:** Test cases:

1. **Rendering:**
   - Editor renders correctly
   - CodeMirror instance is created

2. **Code Changes:**
   - Local changes emit CODE_CHANGE event
   - Remote changes update editor
   - No infinite loops

3. **Socket Events:**
   - Handles CODE_CHANGE events
   - Cleans up listeners on unmount

4. **Edge Cases:**
   - Null/undefined code handling
   - Empty code handling
   - Very long code handling

---

## Deployment Questions

### Q51: How would you deploy this application?

**Answer:** Deployment options:

1. **Monolithic Deployment:**
   - Build React app: `npm run build`
   - Copy build folder to backend
   - Deploy single server (Express serves static files)
   - Use PM2 or similar for process management

2. **Separate Deployment:**
   - Frontend: Vercel, Netlify, or S3 + CloudFront
   - Backend: Heroku, AWS EC2, DigitalOcean, or Railway
   - Configure CORS properly
   - Set environment variables

3. **Docker Deployment:**
   - Create Dockerfile for backend
   - Use multi-stage build
   - Deploy with Docker Compose or Kubernetes

### Q52: What environment variables are needed?

**Answer:** Required environment variables:

**Frontend (.env):**
- `REACT_APP_BACKEND_URL`: Backend WebSocket URL (e.g., `http://localhost:5000`)

**Backend (.env):**
- `PORT`: Server port (defaults to 5000)
- `NODE_ENV`: Environment (development/production)
- `FRONTEND_URL`: For CORS configuration
- `JWT_SECRET`: If adding authentication

### Q53: How would you handle production build?

**Answer:** Production build process:

1. **Frontend:**
   ```bash
   cd frontend
   npm run build
   # Creates optimized build/ folder
   ```

2. **Backend:**
   - Copy `frontend/build` to `backend/build`
   - Or configure backend to point to build location
   - Set `NODE_ENV=production`

3. **Optimizations:**
   - Minify JavaScript/CSS
   - Enable gzip compression
   - Use CDN for static assets
   - Enable caching headers

### Q54: What considerations are needed for scaling?

**Answer:** Scaling considerations:

1. **Horizontal Scaling:**
   - Multiple server instances
   - Use Redis adapter for Socket.io (shared state)
   - Load balancer with sticky sessions

2. **Database:**
   - Store room data in database
   - Store user sessions
   - Cache frequently accessed data

3. **Code Execution:**
   - Queue system for code execution
   - Separate execution service
   - Rate limiting per user

4. **Monitoring:**
   - Application performance monitoring
   - Error tracking (Sentry)
   - Logging (Winston, Pino)

---

## Best Practices & Improvements

### Q55: What code quality issues exist?

**Answer:** Issues found:

1. **Commented Code:** Large blocks of commented code should be removed
2. **Console.logs:** Should use proper logging library
3. **Error Handling:** Inconsistent error handling
4. **No TypeScript:** Could benefit from type safety
5. **No ESLint/Prettier:** Code formatting inconsistent
6. **Magic Numbers/Strings:** Some hardcoded values
7. **No Documentation:** Missing JSDoc comments
8. **Inconsistent Naming:** Some inconsistencies

### Q56: How would you improve the code structure?

**Answer:** Improvements:

1. **Separate Concerns:**
   - Create services layer (socketService, apiService)
   - Extract business logic from components
   - Create custom hooks (useSocket, useCodeEditor)

2. **State Management:**
   - Consider Context API or Redux for global state
   - Separate local vs global state

3. **Constants:**
   - Move all constants to separate files
   - Use environment variables properly

4. **Error Boundaries:**
   - Add React Error Boundaries
   - Better error handling

5. **TypeScript Migration:**
   - Gradually migrate to TypeScript
   - Add type definitions

### Q57: What features would you add?

**Answer:** Feature suggestions:

1. **User Features:**
   - User authentication and profiles
   - Room persistence (save/load)
   - Chat functionality
   - Cursor position sync
   - User permissions (read-only, edit)

2. **Editor Features:**
   - Multiple file support
   - File tree navigation
   - Syntax highlighting for all languages
   - Code completion/IntelliSense
   - Find and replace
   - Undo/redo with history

3. **Collaboration:**
   - User cursors with names
   - Selection highlighting
   - Comments/annotations
   - Version history
   - Conflict resolution

4. **Code Execution:**
   - Input support (stdin)
   - Multiple test cases
   - Execution history
   - Share execution results

### Q58: How would you implement cursor position synchronization?

**Answer:** Implementation:

1. **Track Cursor:**
   ```javascript
   editorRef.current.on('cursorActivity', (cm) => {
       const cursor = cm.getCursor();
       socketRef.current.emit(ACTIONS.CURSOR_CHANGE, {
           roomId,
           cursor,
           socketId: socketRef.current.id
       });
   });
   ```

2. **Receive Cursors:**
   ```javascript
   socketRef.current.on(ACTIONS.CURSOR_CHANGE, ({ cursor, socketId, username }) => {
       // Display cursor marker for other users
       // Use CodeMirror addon for remote cursors
   });
   ```

3. **Visual Indicators:**
   - Use CodeMirror addon or custom implementation
   - Show colored cursors with usernames
   - Update in real-time

### Q59: How would you add room persistence?

**Answer:** Implementation:

1. **Database:**
   - Store rooms in database (MongoDB, PostgreSQL)
   - Store code, language, metadata
   - Store user associations

2. **Backend API:**
   ```javascript
   // Save room
   app.post('/api/rooms/:roomId/save', saveRoom);
   // Load room
   app.get('/api/rooms/:roomId', getRoom);
   ```

3. **Auto-save:**
   - Periodically save code
   - Save on disconnect
   - Save on explicit save action

4. **Version History:**
   - Store code versions
   - Allow reverting to previous versions

### Q60: What monitoring and logging would you add?

**Answer:** Monitoring setup:

1. **Logging:**
   - Use Winston or Pino
   - Log levels: error, warn, info, debug
   - Log socket events, errors, API calls
   - Structured logging with context

2. **Error Tracking:**
   - Integrate Sentry
   - Track client and server errors
   - Alert on critical errors

3. **Performance:**
   - Track response times
   - Monitor socket connection counts
   - Track code execution times
   - Monitor memory usage

4. **Analytics:**
   - Track room creation/joins
   - Track code execution frequency
   - Track user engagement

---

## Advanced Questions

### Q61: How would you implement Operational Transforms (OT) or CRDTs?

**Answer:** Implementation approach:

1. **Choose Library:**
   - **OT:** ShareJS, ot.js
   - **CRDT:** Yjs, Automerge

2. **Yjs Example:**
   ```javascript
   import * as Y from 'yjs';
   import { ySyncPlugin } from 'y-prosemirror';
   
   const ydoc = new Y.Doc();
   const provider = new WebsocketProvider('ws://localhost:5000', roomId, ydoc);
   ```

3. **Benefits:**
   - Efficient diffs instead of full code
   - Better conflict resolution
   - Cursor position sync
   - Undo/redo support

### Q62: How would you handle conflicts when two users edit the same line?

**Answer:** Conflict resolution strategies:

1. **Last Write Wins (Current):** Simple but can lose data
2. **Operational Transforms:** Transform operations to resolve conflicts
3. **CRDTs:** Automatically merge changes
4. **Locking:** Lock lines being edited (complex UX)
5. **Conflict Markers:** Show conflicts and let users resolve

**Best Approach:** Use OT or CRDT library for automatic conflict resolution.

### Q63: How would you scale Socket.io to multiple servers?

**Answer:** Scaling approach:

1. **Redis Adapter:**
   ```javascript
   const { createAdapter } = require('@socket.io/redis-adapter');
   const { createClient } = require('redis');
   
   const pubClient = createClient({ host: 'localhost', port: 6379 });
   const subClient = pubClient.duplicate();
   
   io.adapter(createAdapter(pubClient, subClient));
   ```

2. **Load Balancer:**
   - Use sticky sessions (session affinity)
   - Or use Redis adapter (no sticky sessions needed)

3. **Shared State:**
   - Store `userSocketMap` in Redis
   - All servers can access shared state

### Q64: How would you implement user permissions (read-only, edit)?

**Answer:** Implementation:

1. **Room Roles:**
   - Owner: Full control
   - Editor: Can edit
   - Viewer: Read-only

2. **Backend:**
   ```javascript
   const roomPermissions = {
       [roomId]: {
           [username]: 'editor' // or 'viewer'
       }
   };
   
   socket.on(ACTIONS.CODE_CHANGE, ({ roomId, code }) => {
       const permission = roomPermissions[roomId]?.[username];
       if (permission === 'viewer') {
           return; // Reject change
       }
       // Allow change
   });
   ```

3. **Frontend:**
   - Disable editor for viewers
   - Show visual indicator of permission
   - Disable run button for viewers

### Q65: How would you add file upload/download functionality?

**Answer:** Implementation:

1. **Backend API:**
   ```javascript
   app.post('/api/rooms/:roomId/files', uploadFile);
   app.get('/api/rooms/:roomId/files/:filename', downloadFile);
   ```

2. **Socket Events:**
   - `FILE_UPLOAD`: Notify room of new file
   - `FILE_DELETE`: Notify room of deleted file

3. **Frontend:**
   - File input component
   - File list display
   - Download buttons
   - File tree navigation

4. **Storage:**
   - Local filesystem or cloud storage (S3)
   - Associate files with rooms

---

## Summary

This document covers comprehensive interview questions about the CodeConnect application, including:

- **Architecture:** Client-server with WebSocket real-time communication
- **Backend:** Express + Socket.io for room management and code sync
- **Frontend:** React with CodeMirror for collaborative editing
- **Features:** Real-time collaboration, code execution, multi-language support
- **Security:** Current vulnerabilities and improvement strategies
- **Performance:** Optimization opportunities
- **Testing:** Testing strategies and approaches
- **Deployment:** Production deployment considerations
- **Improvements:** Code quality, features, and best practices

The application demonstrates real-time collaboration concepts, WebSocket communication, and modern React patterns, making it a good project for discussing full-stack development skills.

