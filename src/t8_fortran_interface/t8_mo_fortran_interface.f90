module t8_mo_fortran_interface

      use, intrinsic :: ISO_C_BINDING


      !!! Interface for t8_fortran_MPI_Comm_new
      !!! Given a fortran MPI Communicator, converts it into C and
      !!! returns a pointer to the C MPI communicator.
      !!! This function allocates memory that needs to be freed with
      !!! t8_fortran_mpi_comm_delete_f
      !!!
      !!! Code modified from: https://stackoverflow.com/questions/42530620/how-to-pass-mpi-communicator-handle-from-fortran-to-c-using-iso-c-binding
      INTERFACE
          type (C_PTR) FUNCTION t8_fortran_mpi_comm_new_f (FCOMM)         &
                        BIND(C, NAME='t8_fortran_MPI_Comm_new')
              use, intrinsic :: ISO_C_BINDING, only: c_int, c_ptr
              IMPLICIT NONE
              INTEGER (C_INT), VALUE :: Fcomm
          END FUNCTION t8_fortran_mpi_comm_new_f
      END INTERFACE

      !!! Free memory of a C MPI communicator pointer that was
      !!! allocated using t8_fortran_mpi_comm_new_f
      INTERFACE
          subroutine t8_fortran_mpi_comm_delete_f (Ccomm)         &
                        BIND(C, NAME='t8_fortran_MPI_Comm_delete')
              use, intrinsic :: ISO_C_BINDING, only: c_ptr
              IMPLICIT NONE
              type (c_ptr), value :: Ccomm
          END subroutine t8_fortran_mpi_comm_delete_f
      END INTERFACE

      !!! Initialize sc and t8code with a given C MPI Communicator
      Interface
            subroutine t8_fortran_init_all_f (Ccomm)         &
                        BIND(C, NAME='t8_fortran_init_all')
            use, intrinsic :: ISO_C_BINDING, only: c_ptr
            IMPLICIT NONE
            type (c_ptr), value :: Ccomm
            END subroutine t8_fortran_init_all_f
      end Interface

            !!! Initialize sc and t8code with a given C MPI Communicator
      Interface
            subroutine t8_fortran_init_all_noMPI_f ()         &
                        BIND(C, NAME='t8_fortran_init_all_noMPI')
            END subroutine t8_fortran_init_all_noMPI_f
      end Interface

      Interface
            type (c_ptr) function t8_cmesh_new_periodic_tri_f (Ccomm) &
                                    bind (c, name = 't8_cmesh_new_periodic_tri_wrap')
                  use, intrinsic :: ISO_C_BINDING, only: c_ptr
                  IMPLICIT NONE
                  type (c_ptr), value :: Ccomm
            end function t8_cmesh_new_periodic_tri_f
      end Interface

      Interface
            integer (c_int) function t8_cmesh_vtk_write_file_f (cmesh, fileprefix, scale) &
                                    bind (c, name = 't8_cmesh_vtk_write_file')
                  use, intrinsic :: ISO_C_BINDING, only: c_ptr, c_int, c_char, c_double
                  IMPLICIT NONE
                  type (c_ptr), value :: cmesh
                  character (c_char) :: fileprefix
                  real (c_double), value :: scale
            end function t8_cmesh_vtk_write_file_f
      end Interface

      Interface
            subroutine t8_cmesh_destroy_f (cmesh) &
                                    bind (c, name = 't8_cmesh_destroy')
                  use, intrinsic :: ISO_C_BINDING, only: c_ptr
                  IMPLICIT NONE
                  type (c_ptr) :: cmesh
            end subroutine t8_cmesh_destroy_f
      end Interface

      Interface
            subroutine t8_fortran_cmesh_init_f (cmesh) &
                                    bind (c, name = 't8_cmesh_init')
                  use, intrinsic :: ISO_C_BINDING, only: c_ptr
                  IMPLICIT NONE
                  type (c_ptr) :: cmesh
            end subroutine t8_fortran_cmesh_init_f
      end Interface

      Interface
            type (c_ptr) function t8_fortran_geometry_linear_new_f (dimension) &
                                    bind (c, name = 't8_geometry_linear_new')
                  use, intrinsic :: ISO_C_BINDING, only: c_int, c_ptr
                  IMPLICIT NONE
                  integer (c_int), value :: dimension
            end function t8_fortran_geometry_linear_new_f
      end Interface

      Interface
            subroutine t8_fortran_cmesh_register_geometry_f (cmesh, geometry) &
                                    bind (c, name = 't8_cmesh_register_geometry')
                  use, intrinsic :: ISO_C_BINDING, only: c_ptr
                  IMPLICIT NONE
                  type (c_ptr), value :: cmesh
                  type (c_ptr), value :: geometry
            end subroutine t8_fortran_cmesh_register_geometry_f
      end Interface

      Interface
            subroutine t8_fortran_cmesh_set_tree_class_f (cmesh, gtree_id, tree_class) &
                                    bind (c, name = 't8_cmesh_set_tree_class')
                  use, intrinsic :: ISO_C_BINDING, only: c_ptr, c_int64_t, c_int
                  IMPLICIT NONE
                  type (c_ptr), value :: cmesh
                  integer (c_int64_t), value :: gtree_id
                  integer (c_int), value :: tree_class
            end subroutine t8_fortran_cmesh_set_tree_class_f
      end Interface

      Interface
            subroutine t8_fortran_cmesh_set_tree_vertices_f (cmesh, ltree_id, vertices, num_vertices) &
                                    bind (c, name = 't8_cmesh_set_tree_vertices')
                  use, intrinsic :: ISO_C_BINDING, only: c_ptr, c_int, c_int64_t
                  IMPLICIT NONE
                  type (c_ptr), value :: cmesh
                  integer (c_int64_t), value :: ltree_id
                  type(c_ptr),value :: vertices
                  integer (c_int), value :: num_vertices
            end subroutine t8_fortran_cmesh_set_tree_vertices_f
      end Interface

      Interface
            subroutine t8_fortran_cmesh_set_join_f (cmesh, gtree1, gtree2, face1, face2, orientation) &
                                    bind (c, name = 't8_cmesh_set_join')
                  use, intrinsic :: ISO_C_BINDING, only: c_ptr, c_int, c_int64_t
                  IMPLICIT NONE
                  type (c_ptr), value :: cmesh
                  integer (c_int64_t), value :: gtree1
                  integer (c_int64_t), value :: gtree2
                  integer (c_int), value :: face1
                  integer (c_int), value :: face2
                  integer (c_int), value :: orientation
            end subroutine t8_fortran_cmesh_set_join_f
      end Interface
	  
	  Interface
            subroutine t8_fortran_cmesh_set_join_by_vertices_noConn_f (cmesh, ntrees, eclasses, vertices, do_both_directions) &
                                    bind (c, name = 't8_fortran_cmesh_set_join_by_vertices_noConn')
                  use, intrinsic :: ISO_C_BINDING, only: c_ptr, c_int
                  IMPLICIT NONE
                  type (c_ptr), value :: cmesh
                  integer (c_int), value :: ntrees
                  type (c_ptr), value :: eclasses
                  type (c_ptr), value :: vertices
                  integer (c_int), value :: do_both_directions
            end subroutine t8_fortran_cmesh_set_join_by_vertices_noConn_f
      end Interface

      Interface
            subroutine t8_fortran_cmesh_commit_f (cmesh, Ccom) &
                                    bind (c, name = 't8_fortran_cmesh_commit')
                  use, intrinsic :: ISO_C_BINDING, only: c_ptr
                  IMPLICIT NONE
                  type (c_ptr), value :: cmesh
                  type (c_ptr), value :: Ccom
            end subroutine t8_fortran_cmesh_commit_f
      end Interface

      Interface
            type (c_ptr) function t8_forest_new_uniform_default_f (cmesh, level, do_face_ghost, Ccomm) &
                                    bind (c, name = 't8_forest_new_uniform_default')
                  use, intrinsic :: ISO_C_BINDING, only: c_ptr, c_int
                  IMPLICIT NONE
                  type (c_ptr), value :: cmesh
                  integer (c_int), value :: level
                  integer (c_int), value :: do_face_ghost
                  type (c_ptr), value :: Ccomm
            end function t8_forest_new_uniform_default_f
      end Interface


      Interface
            subroutine t8_forest_unref_f (forest) &
                                    bind (c, name = 't8_forest_unref')
                  use, intrinsic :: ISO_C_BINDING, only: c_ptr
                  IMPLICIT NONE
                  type (c_ptr) :: forest
            end subroutine t8_forest_unref_f
      end Interface


      Interface
            integer (c_int) function t8_forest_write_vtk_f (forest, fileprefix) &
                                    bind (c, name = 't8_forest_write_vtk')
                  use, intrinsic :: ISO_C_BINDING, only: c_ptr, c_int, c_char, c_double
                  IMPLICIT NONE
                  type (c_ptr), value :: forest
                  character (c_char) :: fileprefix
            end function t8_forest_write_vtk_f
      end Interface

      Interface
            subroutine t8_forest_iterate_replace_f (forest_new, forest_old, replace_fn) &
                                    bind (c, name = 't8_forest_iterate_replace')
                  use, intrinsic :: ISO_C_BINDING, only: c_ptr
                  IMPLICIT NONE
                  type (c_ptr), value :: forest_new
                  type (c_ptr), value :: forest_old
                  type (c_ptr), value :: replace_fn
            end subroutine t8_forest_iterate_replace_f
      end Interface

      Interface
            subroutine t8_global_productionf_noargs_f (string) &
                                    bind (c, name = 't8_global_productionf_noargs')
                  use, intrinsic :: ISO_C_BINDING, only: c_char
                  IMPLICIT NONE
                  character (c_char) :: string
            end subroutine t8_global_productionf_noargs_f
      end Interface

      Interface
            subroutine t8_fortran_finalize_f () &
                                    bind (c, name = 't8_fortran_finalize')
                  IMPLICIT NONE
            end subroutine t8_fortran_finalize_f
      end Interface

      ! Interface 
      !       type (c_ptr) function t8_fortran_adapt_by_coordinates_f (forest, forest_from, recursive, callback) &
      !                               bind (c, name = 't8_fortran_adapt_by_coordinates')
      !             use, intrinsic :: ICO_C_BINDING, only : c_ptr, c_int
      !             IMPLICIT NONE
      !             type (c_ptr), value :: forest
      !             type (c_ptr), value :: forest_from
      !             integer (c_int), value :: recursive
      !             type (c_ptr), value :: callback
      !       end function t8_fortran_adapt_by_coordinates_f
      ! end Interface

End module t8_mo_fortran_interface