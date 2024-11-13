import { Routes } from '@angular/router';
import { AuthGuard } from '@utills/routeGuard'
export const routes: Routes = [];


// // about
// routes.push({
//   path: 'about-us',
//   loadChildren: () => import('../../../features/about').then(m => m.AboutModule)
// });

// // accounts
// routes.push({
//   path: 'accounts',
//   loadChildren: () => import('../../../features/accounts').then(m => m.AccountsModule),
//   canActivate:[AuthGuard]
// });

// // addCourse
// routes.push({
//   path: 'add-course',
//   loadChildren: () => import('../../../features/addCourse').then(m => m.AddCourseModule)
// });

// // addUser
// routes.push({
//   path: 'add-user',
//   loadChildren: () => import('../../../features/addUser').then(m => m.AddUserModule)
// });

// // applications
// routes.push({
//   path: 'applications',
//   loadChildren: () => import('../../../features/applications').then(m => m.ApplicationsModule)
// });

// // blog
// routes.push({
//   path: 'blog',
//   loadChildren: () => import('../../../features/blog').then(m => m.BlogModule),
//   canActivate:[AuthGuard]
// });

// // courses
// routes.push({
//   path: 'courses',
//   loadChildren: () => import('../../../features/courses').then(m => m.CoursesModule),
//   canActivate:[AuthGuard]
// });

// // dashboard
// routes.push({
//   path: 'dashboard',
//   loadChildren: () => import('../../../features/dashboard').then(m => m.DashboardModule),
//   canActivate:[AuthGuard]
// });

// // events
// routes.push({
//   path: 'events',
//   loadChildren: () => import('../../../features/events').then(m => m.EventsModule),
//   canActivate:[AuthGuard]
// });

// // history
// routes.push({
//   path: 'history',
//   loadChildren: () => import('../../../features/history').then(m => m.HistoryModule),
//   canActivate:[AuthGuard]
// });

// login
routes.push({
  path: 'login',
  loadChildren: () => import('../../../features/login').then(m => m.LoginModule)
});

// // profile
// routes.push({
//   path: 'profile',
//   loadChildren: () => import('../../../features/profile').then(m => m.ProfileModule),
//   canActivate:[AuthGuard]
// });

// // resources
// routes.push({
//   path: 'resources',
//   loadChildren: () => import('../../../features/resources').then(m => m.ResourcesModule),
//   canActivate:[AuthGuard]
// });

// signup
routes.push({
  path: 'signup',
  loadChildren: () => import('../../../features/signup').then(m => m.SignupModule)
});

// // timetable
// routes.push({
//   path: 'timetable',
//   loadChildren: () => import('../../../features/timetable').then(m => m.TimetableModule),
//   canActivate:[AuthGuard]
// });

// // Add new routes before these route
// // 
// routes.push({
//   path: '',
//   loadChildren: () => import('../../../features/homepage').then((m) => m.HomepageModule)
// });

// ** -> wildcard
routes.push({
  path: '**',
  redirectTo: '/',
  pathMatch: 'full'
})

