// // import * as firebase from 'firebase';
// // import 'firebase/auth';
// import firebase from 'firebase/compat/app';
// import 'firebase/compat/auth';
// import 'firebase/compat/firestore';

// import firebaseConfig from './firebaseConfig';

// // Initialize Firebase App
// // if (!firebase.apps.length) {
// //   firebase.initializeApp(firebaseConfig);
// // }

// // global.db = firebase.firestore();

// let app;

// if (firebase.apps.length === 0) {
//   app = firebase.initializeApp(firebaseConfig)
// } else {
//   app = firebase.app();
// }

// const db = app.firestore();
// const auth = firebase.auth();

// export { db, auth };

import { initializeApp } from 'firebase/app';
import { getAuth} from 'firebase/compat/auth';
import { getFirestore, collection, getDocs } from 'firebase/firestore';
// import firebaseConfig from './firebaseConfig'; 

const firebaseConfig = {
  apiKey: "AIzaSyClZJeiw0cpZ3JkwwVczTE2lOFvxKDKajk",
  authDomain: "lahacks-4be07.firebaseapp.com",
  projectId: "lahacks-4be07",
  storageBucket: "lahacks-4be07.appspot.com",
  messagingSenderId: "566228910809",
  appId: "1:566228910809:web:e3a9408f1eac72780db4c8"
};

const app = initializeApp(firebaseConfig);
const db = getFirestore(app);


export { db };
